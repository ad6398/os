#include<bits/stdc++.h>
using namespace std;
class Process
{
	public:
	int pid,at,bt,ct,tat,obt,index;
	Process(int id,int a,int b,int i)
	{
		pid=id;
		at=a;
		bt=b;
		obt=bt;
		index=i;
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
	int tq=3;
	int time=v[0].at;
	int i=0;
	Process *sch=0;
	queue<Process> pq;
	float avgtat=0;
	int te=0;
	while(i<n||sch||!pq.empty())
	{
		while(i<n)
		{
			if(v[i].at==time)
			{
				pq.push(v[i]);
				i++;
			}
			else
				break;
		}	
		if(sch==0)
		{
			if(pq.empty())
			{
				time++;
				continue;
			}
			Process xy=pq.front();
			sch=&xy;
			pq.pop();
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
			else if(te==tq&&!pq.empty())
			{
				cout<<"PID="<<(sch->pid)<<" suspended at time "<<time<<endl;
				pq.push(*sch);
				Process xy=pq.front();
				sch=&xy;
				pq.pop();
				cout<<"PID="<<(sch->pid)<<" running at time "<<time<<endl;
				te=0;	
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
