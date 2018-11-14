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
sem_t *chops[5];
time_t sttime;
time_t time()
{
	return time(NULL)-sttime;
}
void philosopher(int id)
{
	srand(id*getpid());
	
	while(true)
	{	
		//determine what to do;
		if(rand()%2==0)			//with 50% probability think
		{
			int t=rand()%10+1;
			cout<<"Time="<<time()<<" Philosopher "<<id<<" will think for "<<t<<" time"<<endl;
			sleep(t);  
		}
		else					// with 50% probability become hungry
		{
			cout<<"Time="<<time()<<" Philosopher "<<id<<" is hungry now"<<endl;
			int s1=id;
			int s2=(1+id)%5;
			if(s1>s2)
				swap(s1,s2);
			cout<<"Time="<<time()<<" Philosopher "<<id<<" wants to pick up chopstick "<<s1<<endl;
			sem_wait(chops[s1]);
			cout<<"Time="<<time()<<" Philosopher "<<id<<" picked up chopstick "<<s1<<endl;
			cout<<"Time="<<time()<<" Philosopher "<<id<<" wants to pick up chopstick "<<s2<<endl;
			sem_wait(chops[s2]);
			cout<<"Time="<<time()<<" Philosopher "<<id<<" picked up chopstick "<<s2<<endl;
			int t=rand()%10+1;
			cout<<"Time="<<time()<<" Philosopher "<<id<<" will eat for "<<t<<" time"<<endl;
			sleep(t);
			cout<<"Time="<<time()<<" Philosopher "<<id<<" puts down chopstick "<<s1<<endl;
			sem_post(chops[s1]);
			cout<<"Time="<<time()<<" Philosopher "<<id<<" puts down chopstick "<<s2<<endl;
			sem_post(chops[s2]);
		}
	}
}
int main()
{
	chops[0]=sem_open("/chops0",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	chops[1]=sem_open("/chops1",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	chops[2]=sem_open("/chops2",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	chops[3]=sem_open("/chops3",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	chops[4]=sem_open("/chops4",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	int t;
	cout<<"Enter the time(int seconds) for thich the simulation should be run"<<endl;
	cin>>t;
	int pid[5];
	sttime=time(NULL);
	for(int i=0;i<5;i++)
	{
		pid[i]=fork();
		if(pid[i]==0)
		{
			philosopher(i);
			return 0;
		}
	}
	sleep(t);
	for(int i=0;i<5;i++)
		kill(pid[i],SIGKILL);
	for(int i=0;i<5;i++)
		wait(NULL);
	sem_unlink("/chops0");
	sem_unlink("/chops1");
	sem_unlink("/chops2");
	sem_unlink("/chops3");
	sem_unlink("/chops4");
	return 0;	
}
