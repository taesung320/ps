//
// Created by 윤태성 on 2021/12/07.
//
//@TODO : 이분탐색 다익스트라 , 아직 못품
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,int> p;
typedef priority_queue<int,vector<int>,greater<int>> min_pq;
typedef priority_queue<int> max_pq;
typedef pair<pair<int,int>,pair<min_pq,max_pq>> node;
const int INF=1e9;
int dist[1001] = {};
vector<vector<p>> edge;
int N,P,K;
//@TODO : pq 비교 연산자 오버라이딩
struct cmp {
    bool operator()( const node &a,const node &b){
        return (a.first.first < b.first.first);
    }
};
int dk(){
    priority_queue<node,vector<node>,cmp> pq;
    min_pq minpq;
    max_pq maxpq;
    dist[1]=0;
    pq.push({{0,1},{minpq,maxpq}});
    int ret=INF;
    while (!pq.empty()) {
        int cost=pq.top().first.first;
        int cur=pq.top().first.second;
        min_pq free_pq=pq.top().second.first;
        max_pq cost_pq=pq.top().second.second;
        if (cur == N) {
            ret=min(ret,cost);
        }
        pq.pop();
        if(cost>dist[cur]) continue;
        for (int i = 0; i < edge[cur].size(); ++i) {
            int next=edge[cur][i].first;
            int weight=edge[cur][i].second;
            min_pq nFree_pq=free_pq;
            max_pq nCost_pq=cost_pq;
            if (nFree_pq.size() >= K) {
                int temp = nFree_pq.top();
                if(temp<weight){
                    nFree_pq.pop();
                    nFree_pq.push(weight);
                    nCost_pq.push(temp);
                }else{
                    nCost_pq.push(weight);
                }

            }else{
                nFree_pq.push(weight);
            }
            if(nCost_pq.empty()){
                //dist[next]=0;
                pq.push({{dist[next], next},{nFree_pq,nCost_pq}});
            }
            else if(nCost_pq.top()<dist[next]){
                //dist[next]=nCost_pq.top();
                pq.push({{dist[next], next},{nFree_pq,nCost_pq}});
            }
        }
    }
    return ret;
}
int main(){
    cin>>N>>P>>K;
    edge.resize(N+1);
    for (int i = 1; i <= N; ++i) {
        dist[i]=INF;
    }
    for (int i = 0; i < P; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        edge[a].push_back({b,w});
        edge[b].push_back({a,w});
    }
    int ans = dk();
    cout << dist[N];
    cout<<(ans==INF?-1:ans);
}
