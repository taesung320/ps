#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;
typedef pair<int,int> pir;
typedef priority_queue<pir,vector<pir>,greater<pir>> ppq;
const int INF=1e9;
int x,y;
bool isEdge[501][501]={};
vector<vector<pir>> edge;
vector<vector<int>> min_routes;
int solve(int src,int dst);
int dijk_1(int src,int dst);
void remove_edge(int src,int dst);
void init();
int main(){ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
	while(true){
		cin>>x>>y;
		init();
		if(!(x||y)) break;
		int s,d;
		cin>>s>>d;
		for(int i=0;i<y;i++){
			int a,b,w;
			cin>>a>>b>>w;
			isEdge[a][b]=true;
			edge[a].push_back({w,b});
		}
		int ans=solve(s,d);
		cout<<(ans==INF?-1:ans)<<"\n";
	}
}
int solve(int src,int dst){
	int min_dist=dijk_1(src,dst);
	remove_edge(src,dst);
	min_dist=dijk_1(src,dst);
	return min_dist;
}
int dijk_1(int src,int dst){
	vector<int> cost(x);
	for(int i=0;i<x;i++){
		cost[i]=INF;
	}
	cost[src]=0;
	ppq pq;
	pq.push({0,src});
	while(!pq.empty()){
		int here=pq.top().second;
		int dist=pq.top().first;
		pq.pop();
		if(dist>cost[here]) continue;
		for(int i=0;i<edge[here].size();i++){
			int next=edge[here][i].second;
			int n_dist=edge[here][i].first;
			if(!(isEdge[here][next])) continue;
			if(cost[next]>dist+n_dist){//cost 가 바뀌는 순간 , 아니면 지금 cost랑 같은순간...marking 할수있는 요소...인것...같아......
				cost[next]=dist+n_dist;
				pq.push({cost[next],next});
				vector<int> empty_;
				min_routes[next]=empty_;
				min_routes[next].push_back(here);
			}else if(cost[next]==dist+n_dist){
				min_routes[next].push_back(here);
			}
		}
	}
	return cost[dst];
}
void remove_edge(int src,int dst){
	queue<int> q;
	vector<int> visited(x);
	q.push(dst);
	visited[dst]=true;
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		for(int i=0;i<min_routes[cur].size();i++){
			int next=min_routes[cur][i];
			isEdge[next][cur]=false;
			if(visited[next]==false){
				visited[next]=true;
				q.push(next);
			}
		}
	}
}
void init(){
	memset(isEdge,0,sizeof(isEdge));
	min_routes=vector<vector<int>>(x);
	edge=vector<vector<pir>>(x);
	
}