//
// Created by 윤태성 on 2021/12/23.
//

#include<iostream>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,int> p;
const int INF=1e9;
int N,M;
vector<vector<p>> edge;
int getAns(int d){
    vector<bool> visited(N + 1);
    vector<int> val(N + 1);
    priority_queue<p,vector<p>,greater<p>> pq;
    for (int i = 0; i < val.size(); ++i) {
        val[i]=INF;
    }
    pq.push({val[0] = 0,0});
    while(!pq.empty()){
        int cur=pq.top().second;
        int w=pq.top().first;
        pq.pop();
        if(visited[cur]) continue;
        visited[cur]=true;
        val[cur]=w;
        for (int i = 0; i < edge[cur].size(); ++i) {
            int next=edge[cur][i].first;
            int dst=edge[cur][i].second*d;
            pq.push({dst,next});
        }
    }
    int ret=0;
    for (int i = 0; i < val.size(); ++i) {
        ret += val[i];
    }
    return ret*d;
}
int main(){
    cin>>N>>M;
    edge.resize(N+1);
    for (int i = 0; i < M+1; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        w = (w ? 0 : 1);
        edge[a].push_back({b, w});
        edge[b].push_back({a, w});
    }
    int min_ans=getAns(1);
    int max_ans=getAns(-1);
    cout<<max_ans*max_ans-min_ans*min_ans<<endl;
}