#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int D[1001]={};
int indegree[1001]={};
int T,N,K,x,y,w;
vector<int> edge[1001]={};
int main()
{
	cin>>T;
	while(T--)
	{
		bool find_ans=false;
		int ans=-1;
		priority_queue<p,vector<p>,greater<p>> pq;
		cin>>N>>K;
		for(int i=1;i<=N;i++)
			cin>>D[i];
		for(int i=1;i<=K;i++)
		{
			cin>>x>>y;
			edge[x].push_back(y);
			indegree[y]++;
		}
		cin>>w;
		for(int i=1;i<=N;i++)
		{
			if(indegree[i]==0)
			{
				//i==w일땐?
				pq.push({D[i],i});
			}
		}
		int ctl=0;
		while(!pq.empty())
		{
			int cost=pq.top().first;
			int node=pq.top().second;
			pq.pop();
			ctl=cost;
			for(int i=0;i<edge[node].size())
			{
				int next=edge[node][i];
				indegree[next]--;
				if(indegree[next]==0)
					pq.push(next);
			}
		}
	}
}