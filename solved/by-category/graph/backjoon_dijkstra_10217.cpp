#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;
const unsigned int INF=-1;
struct info{
	int dtn;
	int tme;
	int mny;
	info(int _dtn=0,int _tme=0,int _mny=0):dtn(_dtn),tme(_tme),mny(_mny){}
};
typedef pair<int,pair<int,int>> node;
int solve(vector<vector<info>> edge,int M);

int main(){
	int T;
	cin>>T;
	while(T--){
		int N,M,K;
		cin>>N>>M>>K;
		vector<vector<info>> edge(N+1);
		for(int i=0;i<K;i++){
			int u,v,c,d;
			cin>>u>>v>>c>>d;
			edge[u].push_back(info(v,d,c));
			edge[v].push_back(info(v,d,c));
		}
		int ans=solve(edge,M);
		if(ans==INF)
			cout<<"Poor KCM\n";
		else
			cout<<ans<<"\n";
	}
}
int solve(vector<vector<info>> edge,int M){
	int N=edge.size();
	vector<vector<unsigned int>> cost(N);
	for(int i=0;i<N;i++)
		cost[i].resize(M+1);
	for(int i=0;i<N;i++)
		for(int j=0;j<=M;j++)
			cost[i][j]=-1;
	priority_queue<node,vector<node>,greater<node>> pq;
	cost[1][0]=0;
	pq.push({0,{1,0}});//0시간에 1까지 0원 쓰고옴
	while(!pq.empty()){
		int here=pq.top().second.first;
		int spent=pq.top().second.second;
		int timeTo=pq.top().first;
		pq.pop();
		if(cost[here][spent]<timeTo) continue;
		
		for(int i=0;i<edge[here].size();i++){
			int next=edge[here][i].dtn;
			int next_mny=edge[here][i].mny+spent;
			int next_tme=edge[here][i].tme+timeTo;
			if((next_mny<=M)&&(next_tme<cost[next][next_mny])){
				cost[next][next_mny]=next_tme;
				pq.push({next_tme,{next,next_mny}});
			}
		}
	}
	unsigned int ret=-1;
	for(int i=0;i<=M;i++)
		ret=min(cost[N-1][i],ret);
	return ret;
}


