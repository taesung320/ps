
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;
typedef pair<int,int> edge;
const int INF=1e9;
int V,E,a,b,w,s;
vector<edge> ver[20001];
int cost[20001]={};
priority_queue<edge,vector<edge>,greater<edge>> pq;//memset은 1byte 자료형 이외에 모두 0으로 초기화해줘야한다
void dijkstra(int st)
{
		for(int i=1;i<=V;i++)
	{
		cost[i]=INF;
	
	}
	cost[st]=0;
	pq.push(edge(cost[st],st));
	while(!pq.empty())
	{
		int here=pq.top().second;
		int dist=pq.top().first;
		pq.pop();
		if(dist>cost[here])
			continue;
		vector<edge> temp=ver[here];
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
	for(int i=1;i<=V;i++)
	{
		if(cost[i]==INF)
			cout<<"INF\n";
		else
			cout<<cost[i]<<'\n';
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
	}	
	dijkstra(s);
}
