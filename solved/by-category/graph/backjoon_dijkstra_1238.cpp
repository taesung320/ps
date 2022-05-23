
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int,int> edge;
const int INF=1e9;
int V,E,a,b,w,s;
vector<edge> ver[1001];
vector<edge> inver[1001];
int cost1[1001]={};
int cost2[1001]={};
priority_queue<edge,vector<edge>,greater<edge>> pq;
void dijkstra(int st,int type)//반대로 가는걸 구하는것? --> 애초에 반대로 가는 엣지관련한 배열을 만들어놓는다.
{
	int* cost=(type?cost1:cost2);
	for(int i=1;i<=V;i++)//
		cost[i]=INF;
	cost[st]=0;
	pq.push(edge(cost[st],st));
	while(!pq.empty())
	{
		int here=pq.top().second;
		int dist=pq.top().first;
		pq.pop();
		if(dist>cost[here])
			continue;
		vector<edge> temp=(type?ver[here]:inver[here]);
		for(int i=0;i<temp.size();i++)
		{

			int next=temp[i].first;
			int next_cost=temp[i].second;
			if(cost[next]>cost[here]+next_cost)
			{//줄일수있다
				cost[next]=cost[here]+next_cost;
				pq.push(edge(cost[next],next));
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>V>>E>>s;
	for(int i=0;i<E;i++)
	{
		cin>>a>>b>>w;
		ver[a].push_back(edge(b,w));
		inver[b].push_back(edge(a,w));
	}	
	dijkstra(s,0);
	dijkstra(s,1);
	int ans=0;
	for(int i=1;i<=V;i++)
		ans=max(ans,cost1[i]+cost2[i]);
	cout<<ans;
}
