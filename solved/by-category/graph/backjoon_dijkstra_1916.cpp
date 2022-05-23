#include<iostream>
#include<queue>
using namespace std;
#include<vector>
const int INF=1e9;
typedef pair<int,int> pir;
int dijk(vector<vector<pir>> edge,int start,int end){
	vector<int> dstc(edge.size());
	vector<int> newest(edge.size());
	for(int i=1;i<dstc.size();i++){
		dstc[i]=INF;
	}
	
	priority_queue<pir,vector<pir>,greater<pir>> pq;
	pq.push({0,start});
	dstc[start]=0;
	while(!pq.empty()){
		int here=pq.top().second;
		int cost=pq.top().first;
		pq.pop();
		if(cost>dstc[here]) continue;
		
		for(int i=0;i<edge[here].size();i++){
			pir cur_edge=edge[here][i];
			int next=cur_edge.first;
			int next_cost=cost+cur_edge.second;
			if(dstc[next]>next_cost){
				dstc[next]=next_cost;
				newest[next]=here;
				pq.push({next_cost,next});
			}
		}
	}
	cout<<dstc[end]<<endl;
	vector<int> ret;
	int cur=end;
	while(cur!=start){
		ret.push_back(cur);
		cur=newest[cur];
	}
	ret.push_back(start);
	cout<<ret.size()<<endl;
	for(int i=ret.size()-1;i>=0;i--){
		cout<<ret[i]<<" ";
	}
	return dstc[end];
}
int main(){
	int N,M;
	cin>>N>>M;
	vector<vector<pir>> edge(N+1);
	for(int i=0;i<M;i++){
		int s,e,w;
		cin>>s>>e>>w;
		edge[s].push_back({e,w});
	}
	int start,end;
	cin>>start>>end;
	dijk(edge,start,end);
}