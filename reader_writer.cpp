#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
using namespace std;
sem_t *rwMutex,*mutex;
int *readCount=0,*proc=0,*pend=0;
int sttime=0;
time_t time()
{
	return time(NULL)-sttime;
}
void reader()
{
	cout<<"Time="<<time()<<" Reader "<<getpid()<<" is created"<<endl;
	sem_wait(mutex);
	(*readCount)++;
	if((*readCount)==1)
		sem_wait(rwMutex);
	sem_post(mutex);
	cout<<"Time="<<time()<<" Reader "<<getpid()<<" starts reading"<<endl;
	sleep(2);
	cout<<"Time="<<time()<<" Reader "<<getpid()<<" finished reading"<<endl;
	sem_wait(mutex);
	(*readCount)--;
	if((*readCount)==0)
		sem_post(rwMutex);
	sem_post(mutex);
	return ;
	//reader take 2 units of time		
		
}
void writer()
{	
	//writer takes 3 units of time
	cout<<"Time="<<time()<<" Writer "<<getpid()<<" is created"<<endl;
	sem_wait(rwMutex);
	cout<<"Time="<<time()<<" Writer "<<getpid()<<" starts writing"<<endl;
	sleep(3);
	cout<<"Time="<<time()<<" Writer "<<getpid()<<" finished writing"<<endl;
	sem_post(rwMutex); 	
	return;
}
int main()
{
	srand(time(NULL));
	int t;
	int shmid=shmget(2556,4096,0666|IPC_CREAT);
	readCount=(int*)shmat(shmid,(void*)0,0);
	proc=(readCount+1);
	pend=proc;
	rwMutex=sem_open("/rwMutex",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	mutex=sem_open("/mutex",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	cout<<"Enter the time for which simulation should run"<<endl;
	cin>>t;
	sttime=time(NULL);
	for(int i=0;i<t;i++)
	{
		usleep(500000);
		int r=rand()%10;
		if(r<6)							//create a new process with 60% probability each second
		{
			int x=fork();
			if(x==0)
			{
				//determine whether reader or writer
				if(r<3)
				{
					reader();
					return 0;
				}
				else
				{
					writer();
					return 0;
				}
			}
			else
			{
				(*pend)=x;
				pend++;
			} 			
		}
	}
	for(;proc<pend;proc++)
	{
		//kill(*proc,SIGKILL);
		wait(NULL);		
	}
	sem_unlink("/mutex");
	sem_unlink("/rwMutex");
	shmctl(shmid,IPC_RMID,NULL); 
	return 0;	
}
