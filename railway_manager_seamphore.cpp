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
sem_t *north,*south,*east,*west,*mutex,*junc,*val,*commu;
int *count;
time_t sttime;
time_t time()
{
	return time(NULL)-sttime;
}
bool deadlocked()
{
	if(sem_trywait(val)<0)
	{
		cout<<"Time="<<time()<<" System is deadlocked"<<endl;
		return true;
	}
	sem_post(val);
	cout<<"Time="<<time()<<" System is deadlock free"<<endl;
	return false;
}
void North()
{
	cout<<"Time="<<time()<<" North train with pid="<<getpid()<<" created"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests North lock"<<endl;
	sem_wait(north);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired North lock"<<endl;
	sem_wait(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests West lock"<<endl;
	sem_wait(west);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired West lock"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests Junction lock"<<endl;
	sem_wait(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired junction lock; Passing junction"<<endl;
	sleep(2);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing junction lock"<<endl;
	sem_post(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing West lock"<<endl;
	sem_post(west);
	sem_post(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing North lock"<<endl;
	sem_post(north);
	sem_wait(commu);
	(*count)++;
	sem_post(commu);
	return ;
}
void South()
{
	cout<<"Time="<<time()<<" South train with pid="<<getpid()<<" created"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests South lock"<<endl;
	sem_wait(south);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired South lock"<<endl;
	sem_wait(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests East lock"<<endl;
	sem_wait(east);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired East lock"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests Junction lock"<<endl;
	sem_wait(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired junction lock; Passing junction"<<endl;
	sleep(2);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing junction lock"<<endl;
	sem_post(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing East lock"<<endl;
	sem_post(east);
	sem_post(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing South lock"<<endl;
	sem_post(south);
	sem_wait(commu);
	(*count)++;
	sem_post(commu);
	return ;
}
void West()
{
	cout<<"Time="<<time()<<" West train with pid="<<getpid()<<" created"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests West lock"<<endl;
	sem_wait(west);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired West lock"<<endl;
	sem_wait(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests South lock"<<endl;
	sem_wait(south);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired South lock"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests Junction lock"<<endl;
	sem_wait(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired junction lock; Passing junction"<<endl;
	sleep(2);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing junction lock"<<endl;
	sem_post(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing South lock"<<endl;
	sem_post(south);
	sem_post(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing West lock"<<endl;
	sem_post(west);
	sem_wait(commu);
	(*count)++;
	sem_post(commu);
	return ;
}
void East()
{
	cout<<"Time="<<time()<<" East train with pid="<<getpid()<<" created"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests East lock"<<endl;
	sem_wait(east);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired East lock"<<endl;
	sem_wait(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests North lock"<<endl;
	sem_wait(north);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired North lock"<<endl;
	cout<<"Time="<<time()<<" pid="<<getpid()<<"requests Junction lock"<<endl;
	sem_wait(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"acquired junction lock; Passing junction"<<endl;
	sleep(2);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing junction lock"<<endl;
	sem_post(junc);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing North lock"<<endl;
	sem_post(north);
	sem_post(val);
	cout<<"Time="<<time()<<" pid="<<getpid()<<"releasing East lock"<<endl;
	sem_post(east);
	sem_wait(commu);
	(*count)++;
	sem_post(commu);
	return ;
}
int main()
{

	string train;
	cout<<"Enter the string representing the trains"<<endl;
	cin>>train;
	int n=train.length();
	int pid[n];
	north=sem_open("/north",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	south=sem_open("/south",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	east=sem_open("/east",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	west=sem_open("/west",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	mutex=sem_open("/mutex",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	junc=sem_open("/junc",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	val=sem_open("/val",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,4);
	commu=sem_open("/commu",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	int i=0;
	int shmid=shmget(2556,8,0666|IPC_CREAT);
	count=(int*)shmat(shmid,(void*)0,0);
	(*count)=0;
	sttime=time(NULL);
	while(1)
	{
		sleep(1);
		//decide what to do
		if(i<n)
		{
			int r=rand();
			if(r%10<5)	//generate next train with 50% probability
			{
				pid[i]=fork();
				if(pid[i]==0)
				{
					switch(train[i])
					{
						case 'N':North();
						break;
						case 'S':South();
						break;
						case 'E':East();
						break;
						case 'W':West();
						break;
					}
					return 0;
				}
				i++;
			}
			else
			{
				cout<<"Time="<<time()<<" Checking for deadlocks"<<endl;
				if(deadlocked())
				{
					for(int j=0;j<i;j++)
						if(pid[j]!=0)
							kill(pid[j],SIGKILL);
					break;
				}
			}
		}
		else
		{
			cout<<"Time="<<time()<<" Checking for deadlocks"<<endl;
			if(deadlocked())
			{
				for(int j=0;j<i;j++)
					if(pid[j]!=0)
						kill(pid[j],SIGKILL);
				break;
			}
			/*
			for(int j=0;j<i;j++)
			{
				if(pid[j]==0)
					continue;
				cout<<"Checking pid="<<pid[j]<<endl;
				siginfo_t wstatus;
				wstatus.si_pid=0;
				if(waitid(P_PID,pid[j],&wstatus,WNOHANG)!=-1)
				{
					cout<<"pid in wstatus="<<wstatus.si_pid<<endl;
					if(wstatus.si_pid==pid[j])
					{
						cout<<"PID="<<pid[j]<<" Yes"<<endl;
						count++;
						pid[j]=0;	
					}
					else
						cout<<"PID="<<pid[j]<<" No"<<endl;
				}
			}*/
			int x;
			sem_wait(commu);
			x=(*count);
			sem_post(commu);
			if(x==n)
			{
				cout<<"All trains passed through the junction, process completed."<<endl;
				for(int j=0;j<n;j++)
					wait(NULL);
				break;
			}
				
			
			
		}
	}
	sem_unlink("/mutex");
	sem_unlink("/junc");
	sem_unlink("/north");
	sem_unlink("/east");
	sem_unlink("/west");
	sem_unlink("/south");
	sem_unlink("/val");
	sem_unlink("/commu");
	shmctl(shmid,IPC_RMID,NULL); 
	return 0;
}
