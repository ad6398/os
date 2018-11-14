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
time_t sttime;
time_t time()
{
	return time(NULL)-sttime;
}
sem_t *smk[3],*agt,*blk;
string s[3]={"Tobacco","Cigratte Papers","Matches"};
void smoker(int n)
{
	srand(n*time());
	while(true)
	{
		sem_wait(smk[n]);
		int t=rand()%5+1;
		cout<<"Time="<<time()<<" Smoker with "<<s[n]<<" starts preparing ciggratte and will take time "<<t<<endl;
		sleep(t);
		cout<<"Time="<<time()<<" Smoker with "<<s[n]<<" finishes preparing ciggratte."<<endl;
		sem_post(agt);
	}
}
void agent()
{
	srand(getpid()*time());
	while(true)
	{
		sem_wait(agt);
		int x1=rand()%3;
		int x2=rand()%3;
		while(x1==x2)
		{
			x1=rand()%3;
			x2=rand()%3;
		}
		cout<<"Time="<<time()<<" Agent places "<<s[x1]<<" and "<<s[x2]<<" on table"<<endl;
		sem_post(smk[3-x1-x2]);
	}
}
int main()
{
	smk[0]=sem_open("/smk0",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	smk[1]=sem_open("/smk1",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	smk[2]=sem_open("/smk2",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,0);
	agt=sem_open("/agt",O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	int t;
	cout<<"Enter the time(int seconds) for which the simulation should be run"<<endl;
	cin>>t;
	int pid[4];
	sttime=time(NULL);
	for(int i=0;i<3;i++)
	{
		pid[i]=fork();
		if(pid[i]==0)
		{
			smoker(i);
			return 0;
		}
	}
	pid[3]=fork();
	if(pid[3]==0)
	{
		agent();
		return 0;
	}
	sleep(t);
	for(int i=0;i<4;i++)
		kill(pid[i],SIGKILL);
	for(int i=0;i<4;i++)
		wait(NULL);
	sem_unlink("/smk0");
	sem_unlink("/smk1");
	sem_unlink("/smk2");
	sem_unlink("/agt");
	return 0;	
}
