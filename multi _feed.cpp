#include<bits/stdc++.h>
using namespace std;
class Process
{
	public:
	int pid,at,bt,ct,tat,obt,index,curq;
	Process(int id,int a,int b,int i)
	{
		pid=id;
		at=a;
		bt=b;
		obt=bt;
		index=i;
		curq=1;
	}
	
};
bool cmp (Process y,Process x)
{
		return y.at<x.at?true:y.at>x.at?false:y.pid<x.pid;
}
int main()
{
	int n;
	cout<<"Enter the number of processes"<<endl;
	cin>>n;
	vector<Process> v;
	Process pp1(0,0,0,0);
	vector<Process> ans(n+1,pp1);
	for(int i=1;i<=n;i++)
	{
		cout<<"Enter the PID, Arrival Time, Burst time of process "<<i<<endl;
		int a,b,c;
		cin>>a>>b>>c;
		v.push_back(Process(a,b,c,i));
	}
	sort(v.begin(),v.end(),cmp);
	int tq1=4;
	int tq2=8;
	int tq3=12;
	int tq;
	int time=v[0].at;
	int i=0;
	Process *sch=0;
	queue<Process> pq1;
	queue<Process> pq2;
	queue<Process> pq3;
	float avgtat=0;
	int te=0;
	while(i<n||sch||!(pq1.empty()&&pq2.empty()&&pq3.empty()))
	{
		while(i<n)
		{
			if(v[i].at==time)
			{
				pq1.push(v[i]);
				cout<<"PID="<<v[i].pid<<" created and arrived in queue 0 at time="<<time<<endl;
				i++;
			}
			else
				break;
		}	
		if(sch==0)
		{
			if(!pq1.empty())
			{
				Process xy=pq1.front();
				sch=&xy;
				pq1.pop();
				tq=4;
			}
			else if(!pq2.empty())
			{
				Process xy=pq2.front();
				sch=&xy;
				pq2.pop();
				tq=8;
			}
			else if(!pq3.empty())
			{
				Process xy=pq3.front();
				sch=&xy;
				pq3.pop();
				tq=12;
			}
			else
			{
				time++;
				continue;
			}
			cout<<"PID="<<(sch->pid)<<" running at time "<<time<<endl;
			time++;
			te=1;				
		}
		else
		{
			(sch->bt)--;
			int x=(sch->bt);
			if(x==0)
			{
				cout<<"PID="<<(sch->pid)<<" completed at time "<<time<<endl;
				sch->ct=time;
				sch->tat=time-sch->at;
				avgtat+=time-(sch->at);
				ans[sch->index]=*sch;
				sch=0;
				te=-1;
				time--;
			}
			else if(te==tq&&!(pq1.empty()&&pq2.empty()&&pq3.empty()))
			{
				cout<<"PID="<<(sch->pid)<<" suspended at time "<<time<<endl;
				if(sch->curq==1)
				{
					sch->curq=2;
					pq2.push(*sch);
					cout<<"PID="<<sch->pid<<" aged and entered queue 1 at time"<<time<<endl;
				}
				else if(sch->curq==2)
				{
					sch->curq=3;
					cout<<"PID="<<sch->pid<<" aged and entered queue 2 at time"<<time<<endl;
					pq3.push(*sch);
				}
				else
				{
					pq3.push(*sch);
				}
				sch=0;
				time--;
				te=-1;	
			}
			else if(te==tq)
			{
				te=0;
			}
			te++;
			time++;
		}
		
	}
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i].pid<<"\t"<<ans[i].at<<"\t"<<ans[i].obt<<"\t"<<ans[i].ct<<"\t"<<ans[i].tat<<"\t"<<(ans[i].tat-ans[i].obt)<<endl;
	}
	avgtat/=n;
	cout<<"Average turn around time="<<avgtat<<endl;
	return 0;
}
