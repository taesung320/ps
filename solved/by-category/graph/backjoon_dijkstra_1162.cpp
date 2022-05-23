#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
typedef pair<int,int> pir;
typedef pair<ll,pir> node; //{cost,{vtx,packed}}
const  ll INF=1e12;
int main(){
	int N,M,K;
	cin>>N>>M>>K;
	vector<vector<pir>> edge(N+1);
	for(int i=0;i<M;i++){
		int a,b,c;
		cin>>a>>b>>c;
		edge[a].push_back({b,c});
		edge[b].push_back({a,c});
	}
	vector<vector<ll>> cost(N+1);
	for(int i=0;i<cost.size();i++)
		cost[i].resize(K+1);
	for(int i=0;i<cost.size();i++)
		for(int j=0;j<cost[i].size();j++)
			cost[i][j]=INF;
	
	priority_queue<node,vector<node>,greater<node>> pq;
	pq.push({0,{1,0}});
	cost[1][0]=0;
	while(!pq.empty()){
		int here=pq.top().second.first;
		int packed=pq.top().second.second;
		ll dist=pq.top().first;
		pq.pop();
		if(cost[here][packed]<dist) continue;
		
		for(int i=0;i<edge[here].size();i++){
			int next=edge[here][i].first;
			if(packed<K){//포장 가능
				if(cost[next][packed+1]>dist){//포장하면 ㅜ줄어든다
					cost[next][packed+1]=dist;
					pq.push({dist,{next,packed+1}});
				}
			}
			//그냥 이동
			ll next_cost=dist+edge[here][i].second;
			if(cost[next][packed]>next_cost){
				cost[next][packed]=next_cost;
				pq.push({next_cost,{next,packed}});
			}
		}
	}
	ll ret=INF;
	for(int i=0;i<=K;i++){
		ret=min(ret,cost[N][i]);
	}
	cout<<ret;
}


