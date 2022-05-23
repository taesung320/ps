//
// Created by 윤태성 on 2021/12/13.
//

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> p;
typedef pair<int,p> node;
const int none=0;
const int v1=1;
const int v2=2;
const int v1v2=3;
const int INF=1e9;
int V1,V2;
int N,E;
vector<vector<p>> edge;
int cost[801][4]={};
int getNextStt(int next,int stt){
    if (next == V1) {
        if (stt & v1) {
            return stt;
        }else{
            return stt+v1;
        }
    } else if (next == V2) {
        if (stt & v2) {
            return stt;
        } else {
            return stt+v2;
        }
    }else{
        return stt;
    }
}
int djk(){
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < 4; ++j) {
            cost[i][j]=INF;
        }
    }
    priority_queue<node,vector<node>,greater<node>> pq;
    pq.push({0,{1,(V1==1?v1:none)}});
    cost[1][(V1==1?v1:none)]=0;
    while (!pq.empty()) {
        int dist=pq.top().first;
        int cur=pq.top().second.first;
        int stt=pq.top().second.second;
        pq.pop();
        if(dist>cost[cur][stt]) continue;
        for (int i = 0; i < edge[cur].size(); ++i) {
            int next=edge[cur][i].first;
            int next_dist=dist+edge[cur][i].second;
            int next_stt=getNextStt(next,stt);
            if(cost[next][next_stt]>next_dist){
                pq.push({next_dist,{next,next_stt}});
                cost[next][next_stt]=next_dist;
            }
        }
    }
    return cost[N][v1v2];
}
int main(){
    cin>>N>>E;
    edge.resize(N + 1);
    for (int i = 0; i < E; ++i) {
        int a,b,c;
        cin>>a>>b>>c;
        edge[a].push_back({b, c});
        edge[b].push_back({a, c});
    }
    cin>>V1>>V2;
    int ans=djk();
    cout<<(ans==INF?-1:ans)<<"\n";
}
