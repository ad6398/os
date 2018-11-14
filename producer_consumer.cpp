#include<iostream>
#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
#include<semaphore.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
using namespace std;
int BUFFER_SIZE=5;
int *start,*end1,*count;
int *buffer;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int FIN=15;
time_t sttime;
time_t time()
{
	return time(NULL)-sttime;
}
void consumer()
{
	srand(getpid());
	cout<<"Time "<<time()<<" Consumer process created"<<endl;
	for(int i=0;i<FIN;i++)
	{
		sleep(1);
		int d=rand();
		if(d%10<2)	//consumer wants to read;
		{
			cout<<"Time="<<time()<<" consumer wants to read"<<endl;
			sem_wait(mutex);
			if((*count)==0)
			{
				cout<<"Time="<<time()<<" empty buffer. Consumer will need to wait."<<endl;
			}
			sem_post(mutex);
			sem_wait(full);
			sem_wait(mutex);
			(*count)--;
			cout<<"Time="<<time()<<" consumer read item="<<buffer[(*start)]<<endl;
			(*start)++;
			(*start)%=BUFFER_SIZE;
			sem_post(mutex);
			sem_post(empty);
			
		}
	}
}
void producer()
{
	srand(getpid());
	cout<<"Time "<<time()<<" Producer process created"<<endl;
	for(int i=0;i<FIN;i++)
	{
		sleep(1);
		int d=rand();
		if(d%10<7)	//producer wants to produce;
		{
			cout<<"Time="<<time()<<" producer wants to produce"<<endl;
			sem_wait(mutex);
			if((*count)==BUFFER_SIZE)
			{
				cout<<"Time="<<time()<<" full buffer. Producer will need to wait."<<endl;
			}
			sem_post(mutex);
			sem_wait(empty);
			sem_wait(mutex);
			(*count)++;
			cout<<"Time="<<time()<<" producer produced. Item="<<(buffer[(*end1)]=rand())<<endl;
			(*end1)++;
			(*end1)%=BUFFER_SIZE;
			sem_post(mutex);
			sem_post(full);
		}
	}
}
int main()
{
	int shmid=shmget(2556,1024,0666|IPC_CREAT);
	buffer=(int*)shmat(shmid,(void*)0,0);
	start=buffer+5;
	end1=buffer+6;
	count=buffer+7;
	(*start)=(*end1)=(*count)=0;
	sttime=time(NULL);
	mutex=sem_open("/mutex",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	empty=sem_open("/empty",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,BUFFER_SIZE);
	full=sem_open("/full",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	int prod=fork();
	if(prod==0)
	{
		producer();
		return 0;
	}
	int cons=fork();
	if(cons==0)
	{
		consumer();
		return 0;
	}
	sleep(FIN);
	kill(prod,SIGKILL);
	kill(cons,SIGKILL);
	wait(NULL);
	wait(NULL);
	sem_unlink("/mutex");
	sem_unlink("/full");
	sem_unlink("/empty");
	shmctl(shmid,IPC_RMID,NULL); 
	return 0;
}
