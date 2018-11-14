#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,c=0;
	cout<<"Enter the capcaity of buffer"<<endl;
	cin>>n;
	cout<<"Enter the number of requests"<<endl;
	cin>>m;
	cout<<"Enter the request page no."<<endl;
	vector<int> x(m,0);
	for(int i=0;i<m;i++)
		cin>>x[i];
	vector<int> tab;
	set<int> s;
	for(int i=0;i<m;i++)
	{
		if(s.find(x[i])!=s.end())
		{
			cout<<"Entry found in buffer"<<endl;
		}
		else
		{
			cout<<"Page fault occured!"<<endl;
			if(tab.size()==n)
			{
				int tbd=-1,nc=0;
				for(int j=0;j<n;j++)
				{
						int oc=m;
						for(int k=i+1;k<m;k++)
							if(x[k]==tab[j])
							{
								oc=k;
								break;
							}
						if(oc>nc)
						{
							tbd=j;
							nc=oc;
						}
								
				}
				tbd=tab[tbd];
				tab.erase(find(tab.begin(),tab.end(),tbd));
				s.erase(s.find(tbd));
			}
			cout<<x[i]<<" Entered into table"<<endl;
			s.insert(x[i]);
			tab.push_back(x[i]);
			c++;		
		}
	}
	
	cout<<"Total number of page faults="<<c<<endl;
}
