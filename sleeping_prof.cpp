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
int start;
sem_t *students;
sem_t *professor;
sem_t *teaching;
int *techng=0;
sem_t * mutex;
int *studentCount=0;
int chairs=4;
int SHMID=5678;
/*first determine if the professor is sleeping. If yes then wake him up and 
make him busy. otherwise if space is available go to waiting otherwise die.
when professor finishes his job determine if there are peopole waiting if
yes then increase their semaphore and get busy otherwise sleep
*/
void Professor()
{
	while(true)
	{
		//if currently teaching continue;
		sem_wait(teaching);
		if((*techng)==1)
		{
			sem_post(teaching);
			continue;
		}
		else
			sem_post(teaching);
		sem_wait(mutex);
		if((*studentCount)==0)
		{
			cout<<"Time="<<(time(NULL)-start)<<" Professor will go to sleep"<<endl;
		}
		sem_post(mutex);
		sem_wait(students);
		{
			sem_wait(mutex);
			(*studentCount)--;
			sem_post(professor);
			sem_post(mutex);
			sem_wait(teaching);
			(*techng)=1;
			sem_post(teaching);	
		}
	}
}
void Student(int t)
{
	cout<<"Time="<<(time(NULL)-start)<<" Student id="<<getpid()<<" arrived"<<endl;
	sem_wait(mutex);
	if((*studentCount)<chairs)
	{
		if((*studentCount)==0)
		{
			sem_wait(teaching);
			if((*techng)==0)
			{
				cout<<"Time="<<(time(NULL)-start)<<" Professor woke up"<<endl;
				(*techng)=1;
			}
			sem_post(teaching);
		}
		(*studentCount)++;
		sem_post(students);
		sem_post(mutex);
		sem_wait(professor);
		
		cout<<"Time="<<(time(NULL)-start)<<" Student id="<<getpid()<<" is being taught and requires "<<t<<" time"<<endl;
		sleep(t);
		sem_wait(teaching);
		(*techng)=0;
		cout<<"Time="<<(time(NULL)-start)<<" Student id="<<getpid()<<" process completed"<<endl; 
		sem_post(teaching);
	}
	else
	{
		sem_post(mutex);
		cout<<"Time="<<(time(NULL)-start)<<" Student id="<<getpid()<<" returns due to non availability of empty chairs"<<endl;
	}
}
int main()
{
	int shmid=shmget(SHMID,1024,0666|IPC_CREAT);
	studentCount=(int*)shmat(shmid,(void*)0,0);
	techng=studentCount;
	techng++;
	mutex=sem_open("/mutex",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	students=sem_open("/students",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	professor=sem_open("/professor",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	teaching=sem_open("/teaching",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	start=time(NULL);
	int prof=fork();
	int cnt=1;
	if(prof==0)
	{
		Professor();
		return 0;
	}
	for(int i=0;i<15;i++)
	{
		sleep(1);
		int t=rand();
		t%=15;
		t++;
		if(t%2==0)
		{
			cnt++;
			int chld=fork();
			if(chld==0)
			{
				Student(t);
				return 0;	
			}
		}
	}
	for(int i=1;i<cnt;i++)
		wait(NULL);
	kill(prof,SIGKILL);
	sem_unlink("/mutex");
	sem_unlink("/students");
	sem_unlink("/professor");
	sem_unlink("/teaching");
	shmctl(shmid,IPC_RMID,NULL); 
	return 0;
}
