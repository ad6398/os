#include<bits/stdc++.h>
using namespace std;
int allocation[100][100],maxi[100][100],need[100][100],available[100],sq[100],r,n,temp[100];
bool valid()
{
bool res=0;
int i,j,k;
int ch[n];
for(i=0;i<n;i++)
ch[i]=available[i];
for(i=0;i<n;i++)
{
for(j=0;j<r;j++)
{
if(ch[j]>=need[sq[i]][j])
ch[j]+=allocation[sq[i]][j];
else
return res;
}
}
return true;
}
int main()
{
int i,j,k,count,count1=0;
cout<<"Enter number of processes running :";
cin>>n;
cout<<"Enter the number of resources :";
cin>>r;
cout<<"Enter the allocation matrix for the processes in row major order..:\n";
for(i=0;i<n;i++)
{
cout<<"Process "<<i<<endl;
for(j=0;j<r;j++)
cin>>allocation[i][j];
}
cout<<"Enter the no. of resources that a process can maximum have.."<<endl;
for(i=0;i<n;i++)
{
cout<<"Process "<<i<<endl;
for(j=0;j<r;j++)
cin>>maxi[i][j];
}
cout<<"Enter the no. of available instances of each resource.."<<endl;
for(i=0;i<r;i++)
cin>>available[i];
cout<<"The need matrix is as follows : \n";
for(i=0;i<n;i++)
{
for(j=0;j<r;j++)
{
need[i][j]= maxi[i][j]-allocation[i][j];

cout<<" "<<need[i][j];
}
cout<<endl;
}
int t,pid,res,val;
cout<<"\nEnter Number of Requests : ";
cin>>t;
cout<<endl;
while(t)
{
cout<<"Enter Process: ";
cin>>pid;
if(pid<0 || pid>2)
{
cout<<"\nEnter Valid Request.\n";
continue;
}
bool flag=1;
for(i=0;i<r;i++)
{
cin>>val;
temp[i]=val;
if(val>need[pid][i])
flag=0;
}
for(i=0;i<n;i++)
{
sq[i]=i;
if(available[i]<temp[i])
flag=0;
}
if(!flag)
{
cout<<"\nRequest can not be permitted.\n";
t--;
continue;
}
flag=0;
for(i=0;i<r;i++)
{
available[i]-=temp[i];
allocation[pid][i]+=temp[i];
need[pid][i]-=temp[i];
}
do
{
if(valid())
{
cout<<"\nSafeState and Hence Request can be permitted.\nValid Sequence is: ";
for(i=0;i<n;i++)
cout<<sq[i]<<" ";
cout<<endl;
flag=1;
break;
}
}while(next_permutation(sq,sq+n));
if(!flag)
cout<<"\nRequest can not be permitted.\n";
for(i=0;i<r;i++)
{

need[pid][i]+=temp[i];
available[i]+=temp[i];
allocation[pid][i]-=temp[i];
}
t--;
}
}
