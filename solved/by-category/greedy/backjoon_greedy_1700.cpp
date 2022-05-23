#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int> p;
vector<p> con;
priority_queue<int,vector<int>,greater<int>> arr[101];
int ip[100]={};
bool yn[101]={};
int main()
{
	int N,K;
	cin>>N>>K;
	for(int i=0;i<K;i++)
	{
		int a;
		cin>>ip[i];
		arr[ip[i]].push(i);
	}
	int cnt=0;
	for(int i=0;i<K;i++)
	{
		int temp=1000;
		if(!arr[ip[i]].empty())
		{
			arr[ip[i]].pop();
			if(!arr[ip[i]].empty())
			temp=arr[ip[i]].top();//다음거 저장
			else
				arr[ip[i]].push(temp);
		}
		else
			arr[ip[i]].push(temp);//다음거없을때 1000들어가면서 먼저나오게 보장
		if(yn[ip[i]]==true)
			{
				for(int j=0;j<con.size();j++)
				{
					if(con[j].second==ip[i])
						con[j].first=temp;
				}
				continue;
			}
		if(con.size()<N)
		{
			con.push_back({temp,ip[i]});
		}
		else
		{
			
			sort(con.begin(),con.end());
			int la=con.size()-1;
			yn[con[la].second]=false;
			con[con.size()-1]={temp,ip[i]};
			cnt++;
		}
		yn[ip[i]]=true;
	}
	cout<<cnt;
}
