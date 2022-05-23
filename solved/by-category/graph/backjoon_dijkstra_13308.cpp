#include<iostream>
#include<queue>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> edge;
typedef pair<long long int,pair<int,int>> info;
priority_queue<info,vector<info>,greater<info>> pq;
const int SIZ=2501;
const long long int INF=15625000001;
vector<edge> node[SIZ];
long long int dstc[SIZ][SIZ]={};//[정점까지 최소거리][그때 최소단위기름값]<--상태를 수로 이차원배열 사용할수있는것 생각
int oil_cost[SIZ]={};
int N,M,a,b,w;//임력받을것들
long long int dijk()
{
	for(int i=1;i<=N;i++)
		for(int j=1;j<SIZ;j++)
			dstc[i][j]=INF;
	dstc[1][oil_cost[1]]=0;
	pq.push({0,{1,oil_cost[1]}});
	while(!pq.empty())
	{
		int cur=pq.top().second.first;
		int min_oil=pq.top().second.second;
		long long int cost=pq.top().first;
		pq.pop();
		if(cur==N||dstc[cur][min_oil]<cost) continue;
		for(int i=0;i<node[cur].size();i++)
		{
			int next=node[cur][i].second;
			int next_dstc=node[cur][i].first;
			int next_min=min(min_oil,oil_cost[next]);
			long long int temp=cost+next_dstc*min_oil;
			if(dstc[next][min_oil]>temp)
			{
				dstc[next][min_oil]=temp;
				pq.push({dstc[next][min_oil],{next,next_min}});
			}
		}
	}
	long long int rt=INF;
	for(int i=1;i<SIZ;i++)
		rt=min(rt,dstc[N][i]);
	return rt;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>M;
	for(int i=1;i<=N;i++)
	{
		cin>>oil_cost[i];
	}
	for(int i=0;i<M;i++)
	{
		cin>>a>>b>>w;
		node[a].push_back({w,b});
		node[b].push_back({w,a});
	}
	long long int ans=dijk();
	cout<<ans;
}
////////////////////////////
///////////////////
///////그리디,라인스위핑
///////플로이드,비트완탐
///////mst,trie,위상정렬
///////UINION FIND
///////세그먼트트리