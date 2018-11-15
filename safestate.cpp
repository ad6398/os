
#include<bits/stdc++.h>
using namespace std;
int allocation[100][100],maxi[100][100],need[100][100],available[100],sq[100],r,n;
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
cout<<"Process "<<i+1<<endl;
for(j=0;j<r;j++)
cin>>allocation[i][j];
}
cout<<"Enter the no. of resources that a process can maximum have.."<<endl;
for(i=0;i<n;i++)
{
cout<<"Process "<<i+1<<endl;
for(j=0;j<r;j++)
cin>>maxi[i][j];
}
cout<<"Enter the no. of available instances of each resource.."<<endl;
for(i=0;i<r;i++)
cin>>available[i];cout<<"The need matrix is as follows : \n";
for(i=0;i<n;i++)
{
for(j=0;j<r;j++)
{
need[i][j]= maxi[i][j]-allocation[i][j];
cout<<" "<<need[i][j];
}
cout<<endl;
}
for(i=0;i<r;i++)
{
for(j=0;j<n;j++)
available[i]-=allocation[j][i];
}
for(i=0;i<n;i++)
sq[i]=i;
count=0;
cout<<"\nSafe States:\n";
do
{
if(valid())
{
count++;
for(i=0;i<n;i++)
cout<<sq[i]<<" ";
cout<<endl;
}
}while(next_permutation(sq,sq+n));
cout<<"Total Number of Safe States are : "<<count<<endl;
}
