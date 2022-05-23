#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,int> pir;
typedef pair<pir,int> node;
vector<vector<pir>> edge;
vector<int> nomi;
/*
	최단경로에 g-h가 포함되어 있는지
	1. 거의 최단경로 처럼 저장하고 찾아내기
	2. 하는 도중에 --> cost 랑 같은거까진 넣어주고 passed 여부만 달라지게 넣고 passed상태로 도착하면 표시
*/
const int PASSED=1;
const int NOTYET=0;
const int INF=1e9;
void solve(vector<vector<pir>> edge,vector<int> nomi,int s,int g,int h);
int main(){ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,m,t,s,g,h,a,b,d,x;
		cin>>n>>m>>t>>s>>g>>h;
		vector<vector<pir>> edge(n+1);
		vector<int> nomi;
		for(int i=0;i<m;i++){
			cin>>a>>b>>d;
			edge[a].push_back({b,d});
			edge[b].push_back({a,d});
		}
		for(int i=0;i<t;i++){
			cin>>x;
			nomi.push_back(x);
		}
		solve(edge,nomi,s,g,h);
	}
}
//초기화해야할 값을 간과했음.
//문제에는 무조건 도착한다는 보장이 없었는데 있다고 가정함
//visit의 사용여부 생각 못함 ->ㅁ ㅔ모리 초과뜨고 생각함
void solve(vector<vector<pir>> edge,vector<int> nomi,int s,int g,int h){
	priority_queue<node,vector<node>,greater<node>> pq;	
	vector<int> cost(edge.size());
	vector<bool> ret(edge.size());
	for(int i=0;i<cost.size();i++)
		cost[i]=INF;
	pq.push({{0,NOTYET},s});
	cost[s]=0;
	while(!pq.empty()){
		int here=pq.top().second;
		int dist=pq.top().first.first;
		int stt=pq.top().first.second;
		pq.pop();
 
		if(dist>cost[here]) continue;
		for(int i=0;i<edge[here].size();i++){
			int next=edge[here][i].first;
			int next_cost=dist+edge[here][i].second;
			bool isOn=(here==g&&next==h)||(here==h&&next==g);
			int next_stt=(isOn)?PASSED:stt;
			
			if((cost[next]==next_cost)&&next_stt==PASSED){
				if(ret[next]==PASSED) continue;
				ret[next]=PASSED;
				pq.push({{next_cost,PASSED},next});
			}else if(cost[next]>next_cost){
				ret[next]=next_stt;
				cost[next]=next_cost;
				pq.push({{next_cost,next_stt},next});
			}
		}
	}
	sort(nomi.begin(),nomi.end());
	for(int i=0;i<nomi.size();i++){
		if(ret[nomi[i]]==PASSED)
			cout<<nomi[i]<<" ";
	}
	cout<<"\n";
}



