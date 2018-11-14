#include<bits/stdc++.h>
using namespace std;
class Process
{
	public:
	int pid,at,bt,ct,tat,index,obt;
	Process(int id,int a,int b,int i)
	{
		index=i;
		pid=id;
		at=a;
		obt=bt=b;
	}
};
bool cmp (Process y,Process x)
{
		return y.at<x.at?true:y.at>x.at?false:y.pid<x.pid;
}
class cmpq
{
public:
	bool operator() (Process y,Process x)
	{
		return y.bt>x.bt?true:y.bt<x.bt?false:cmp(x,y);
	}
};
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
	int time=v[0].at;
	int i=0;
	Process *sch=0;
	priority_queue< Process,vector<Process>,cmpq> pq;
	float avgtat=0,avgwt=0;
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
			Process xy=pq.top();
			sch=&xy;
			pq.pop();
			cout<<"PID="<<(sch->pid)<<" running at time "<<time<<endl;
			time++;				
		}
		else
		{
			(sch->bt)--;
			int x=(sch->bt);
			if(x==0)
			{
				cout<<"PID="<<(sch->pid)<<" completed at time "<<time<<endl;
				sch->ct=time;
				sch->tat=sch->ct-sch->at;
				avgtat+=(sch->tat);
				ans[sch->index]=*sch;
				sch=0;
				time--;
			}
			time++;
		}
		
	}
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i].pid<<"\t"<<ans[i].at<<"\t"<<ans[i].obt<<"\t"<<ans[i].ct<<"\t"<<ans[i].tat<<"\t"<<(ans[i].tat-ans[i].obt)<<endl;
		avgwt+=(ans[i].tat-ans[i].obt);
	}
	avgtat/=n;
	avgwt/=n;
	cout<<"Average turn around time= "<<avgtat<<endl;
	cout<<"Average waiting time= "<<avgwt<<endl;
	return 0;
}
