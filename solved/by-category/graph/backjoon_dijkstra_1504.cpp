#include<iostream>
#include<algorithm>
using namespace std;
#include<queue>
#include<vector>
#include<utility>
typedef pair<int,int> edge;
vector<edge> vtx[801];
priority_queue<edge,vector<edge>,greater<edge>> pq;
int result[4][4]={};
int N,E,v1,v2,a,b,w;
const int INF=1001;
const int st=0,v1i=1,v2i=2,ed=3;
int nodeToi(int i)
{
	if(i==1)
		return 0;
	else if(i==v1)
		return 1;
	else if(i==v2)
		return 2;
	else if(i==N)
		return 3;
	else
		return INF;
}
void dijk(int s)
{
	int dstc[801]={};
	for(int i=1;i<=N;i++)
		dstc[i]=INF;
	dstc[s]=0;
	pq.push({0,s});
	while(!pq.empty())
	{
		int cur=pq.top().second;
		int cur_cost=pq.top().first;
		pq.pop();
		if(cur_cost>dstc[cur])
			continue;
		for(int i=0;i<vtx[cur].size();i++)
		{
			int next=vtx[cur][i].second;
			int next_cost=vtx[cur][i].first;
			if(dstc[next]>cur_cost+next_cost)
			{
				dstc[next]=cur_cost+next_cost;
				pq.push({dstc[next],next});
			}
		}
	}
	int now_i=nodeToi(s);
	result[now_i][st]=result[st][now_i]=dstc[1];
	result[now_i][v1i]=result[v1i][now_i]=dstc[v1];
	result[now_i][v2i]=result[v2i][now_i]=dstc[v2];
	result[now_i][ed]=result[ed][now_i]=dstc[N];
}
//중복을 최소화 하는것에 있어서 생각을 좀 더했어야 했다.
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>E;
	for(int i=0;i<E;i++)
	{
		cin>>a>>b>>w;
		vtx[a].push_back({w,b});
		vtx[b].push_back({w,a});
	}
	cin>>v1>>v2;
		for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			result[i][j]=INF;
	dijk(1);dijk(v1);dijk(v2);
	if(v1==1)
		result[0][1]=result[1][0]=0;
	if(v2==1)
		result[0][2]=result[2][0]=0;
	if(v1==N)
		result[1][3]=result[3][1]=0;
	if(v2==N)
		result[2][3]=result[3][2]=0;
	int ans=min(result[0][1]+result[2][3]+result[1][2],result[0][2]+result[1][3]+result[1][2]);

	if(ans>=INF)
		ans=-1;
	cout<<ans;
}