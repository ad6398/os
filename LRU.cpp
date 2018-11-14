#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,c=0;
	cout<<"Enter the capcaity of buffer"<<endl;
	cin>>n;
	cout<<"Enter the number of requests"<<endl;
	cin>>m;
	map<int,int> m1,m2;
	cout<<"Enter the request page no."<<endl;
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		if(m1.find(x)!=m1.end())
		{
			cout<<"Entry found in buffer"<<endl;
			m2.erase(m2.find(m1[x]));
			m1[x]=i;
			m2[i]=x;
		}
		else if(m1.size()==n)
		{
			cout<<"Page fault occured!"<<endl;
			int tbr=(*m2.begin()).second;
			m2.erase(m2.begin());
			m1.erase(m1.find(tbr));
			m1[x]=i;
			m2[i]=x;
			cout<<tbr<<" removed from table"<<endl;
			cout<<x<<" Entered into table"<<endl;
			c++;
		}
		else
		{
			cout<<"Page fault occured!"<<endl;
			cout<<x<<" Entered into table"<<endl;
			m1[x]=i;
			m2[i]=x;
			c++;
			
		}
		
		
	}
	cout<<"Total number of page faults="<<c<<endl;
}
