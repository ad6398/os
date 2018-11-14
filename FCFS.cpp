#include<bits/stdc++.h>
using namespace std;
class Process
{
	public:
	int pid,at,bt,obt,ct,tat,index;
	Process(int id,int a,int b,int i)
	{
		pid=id;
		at=a;
		obt=bt=b;
		index=i;
	}
	
};
bool cmp (Process y,Process x)
{
		return y.at<x.at?true:y.at>x.at?false:y.pid<x.pid;
}
bool cmp2(Process y,Process x)
{
	return y.index<x.index;
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
	int time=v[0].at;
	float avgtat=0,avgwt=0;
	for(int i=0;i<n;i++)
	{
		cout<<"PID "<<v[i].pid<<" started at time "<<time<<endl;
		time+=v[i].bt;
		cout<<"PID "<<v[i].pid<<" completed at time "<<time<<endl;
		v[i].ct=time;
		v[i].tat=time-v[i].at;
		ans[v[i].index]=v[i];
		avgtat+=v[i].tat;
	}
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i].pid<<"\t"<<ans[i].at<<"\t"<<ans[i].obt<<"\t"<<ans[i].ct<<"\t"<<ans[i].tat<<"\t"<<(ans[i].tat-ans[i].obt)<<endl;
		avgwt+=(ans[i].tat-ans[i].bt);
	}
	avgtat/=n;
	avgwt/=n;
	cout<<"Average turn around time= "<<avgtat<<endl;
	cout<<"Average waiting time= "<<avgwt<<endl;
	return 0;
}
