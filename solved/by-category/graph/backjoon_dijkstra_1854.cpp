#include<iostream>
#include<utility>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,int> edge;
typedef priority_queue<int> i_pq;
const int INF=1e9;
int N,M,K;
vector<edge> eg[1001];
i_pq ans[1001];
void dij(){
	priority_queue<edge,vector<edge>,greater<edge>> pq;
	ans[1].push(0);
	pq.push({0,1});
	while(!pq.empty()){
		int here=pq.top().second;
		int dist=pq.top().first;
		pq.pop();
		for(int i=0;i<eg[here].size();i++){
			int next=eg[here][i].first;
			int n_dist=eg[here][i].second;
			edge temp={dist+n_dist,next};
		 	if(ans[next].size()>=K){//경로 길이가 무한정 들어오면 안되는건 알았는데
				//이런식으로 생각을 못했다. + 다익스트라 코드만 알고 다른건 재대로 모르고 있었다
				//
				if(ans[next].top()>dist+n_dist)
					ans[next].pop();
				else
					continue;
			}
			pq.push(temp);
			ans[next].push(dist+n_dist);
		}
	}
}
int main(){
	cin>>N>>M>>K;
	for(int i=0;i<M;i++){
		int a,b,w;
		cin>>a>>b>>w;
		eg[a].push_back({b,w});
	}
	dij();
	for(int i=1;i<=N;i++){
		cout<<(ans[i].size()==K?ans[i].top():-1)<<"\n";
	}
}