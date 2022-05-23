#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
#define MAX_N 1001
#define MAX_K 30002
#define MAX_COST 1000010
int N,M,K;
typedef pair<int,int> edge;
vector<edge> edges[MAX_N];
int cost[MAX_N][MAX_N];
int tax[MAX_K];
struct node{
    int cost;
    int dest;
    int path_len;
    bool operator()(const node n1,const node n2){
        if(n1.cost!=n2.cost) return n1.cost>n2.cost;
        return false;
    }
};
void dijk(int s,int d);
int main(){
    int S,D;
    cin>>N>>M>>K>>S>>D;
    memset(cost, 0x3f, sizeof(cost));
    for (int i = 0; i < M; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        edges[a].push_back({b, w});
        edges[b].push_back({a, w});
    }
    for (int i = 1; i < K+1; ++i) {
        cin >> tax[i];
    }
    dijk(S, D);
    vector<int> valid;
    for (int j = 1; j <N ; ++j) {
        if(cost[j][D]<=MAX_COST){
            valid.push_back(j);
        }
    }
    vector<int> results;
    for (int i = 0; i < K+1; ++i) {
        int min_cost=1e9;
        for (int v:valid) {
            cost[v][D]+=(v*tax[i]);
            if(cost[v][D]<min_cost){
                min_cost=cost[v][D];
            }
        }
        results.push_back(min_cost);
    }
    for (int res:results) {
        cout<<res<<'\n';
    }
}

void dijk(int s,int d){
    priority_queue<node,vector<node>,node>  pq;
    cost[0][s]=0;
    pq.push({0,s,0});
    while (!pq.empty()) {
        node cur=pq.top();
        pq.pop();

        if(cur.dest==d) continue;
        if(cur.path_len==N-1) continue;
        if(cost[cur.path_len][cur.dest]<cur.cost) continue;

        for (edge e:edges[cur.dest]) {
            int des=e.first;
            int cos=e.second;
            node next={cos+cur.cost,
                       des,
                       cur.path_len+1};

            if(cost[next.path_len][des]>next.cost){
                cost[next.path_len][des]=next.cost;
                pq.push(next);
            }
        }
    }
}
