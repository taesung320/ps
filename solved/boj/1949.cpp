//
//  1949.cpp
//  boj
//  *** 무방향 그래프 트리로 만들기
//  Created by 윤태성 on 2021/07/21.
//
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int cache[10001][2][2]={};
const int nomal=0;
const int special=1;
const int iINF=-1e9;
int arr[10001]={};
int N;
bool visited[10001]={};
vector<vector<int>> graph;
int solve();
int dp(int tnum,int pstt,int cstt);
int main(){
    int N;
    cin>>N;
    fill(&cache[0][0][0],&cache[N+1][1][1],iINF);
    for (int i=1; i<=N; i++) {
        cin>>arr[i];
    }
    graph.resize(N+1);
    for (int i=0; i<N-1; i++) {
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    //***
    queue<int> q;
    q.push(1);
    visited[1]=true;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            int next=graph[cur][i];
            if(visited[next]==true){
                graph[cur][i]=-1;
            }else{
                visited[next]=true;
                q.push(next);
            }
        }
    }
    //***
    cout<<max(dp(1,0,1),dp(1,0,0));
}

int dp(int num,int pstt,int cstt){
    int& ret=cache[num][pstt][cstt];
    if(ret!=iINF) return ret;
    ret=(cstt==special?arr[num]:0);
    bool check=false;
    int spare=0;
    for(int i=0;i<graph[num].size();i++){
        int child=graph[num][i];
        if(child==-1) continue;
        if(cstt==special) ret+=dp(child,cstt,nomal);
        else{
            int nC=dp(child,cstt,nomal);
            int sC=dp(child,cstt,special);
            if(nC<sC) check=true;
            else{
                spare= min(spare,nC-sC);
            }
            ret+=max(nC,sC);
        }
    }
    if(cstt==nomal&&pstt==nomal&&check==false)
        ret-=spare;
    return ret;
}
