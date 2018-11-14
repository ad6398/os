#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,c=0;
	cout<<"Enter the capcaity of buffer"<<endl;
	cin>>n;
	cout<<"Enter the number of requests"<<endl;
	cin>>m;
	queue<int> q;
	set<int> s;
	cout<<"Enter the request page no."<<endl;
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		if(s.find(x)!=s.end())
		{
			cout<<"Entry found in buffer"<<endl;
		}
		else
		{
			cout<<"Page fault occured!"<<endl;
			if(q.size()==n)
			{
				int tbr=q.front();
				q.pop();
				cout<<tbr<<" removed from table"<<endl;
				s.erase(s.find(tbr));
			}
			cout<<x<<" Entered into table"<<endl;
			s.insert(x);
			q.push(x);
			c++;		
		}
	}
	cout<<"Total number of page faults="<<c<<endl;
}
