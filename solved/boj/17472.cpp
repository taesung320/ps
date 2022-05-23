//
//  17472.cpp
//  boj
//
//  Created by 윤태성 on 2021/07/19.
//
/*
    bfs 마킹 (유니온 파인드 써도됨)
    detect cycle - 양방향 , 단방향 인지 확인하고 알맞게 해야함
    mst(크루스칼)~ 다른 방법은 모름;
 */

#include<iostream>
#include<queue>
#include<utility>
#include<vector>
using namespace std;
typedef pair<int,int> p;
typedef pair<int,p> info;
typedef priority_queue<info,vector<info>,greater<info>> infopq;
int N,M;
int edge[100][100]={};
const int INF=1e9;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int arr[100][100]={};
bool visited[100][100]={};
int island=0; //섬의 개수
bool rangeCheck(int x,int y){
    return (0<=x&&x<N&&0<=y&&y<M);
}
void initIsland(int i,int j);
void findWay(int i,int j);

int ans(infopq q);
bool findCycle(int start,vector<vector<int>> table);
int main(  ){
    cin>>N>>M;
    for (int i=0;i<N; i++) {
        for (int j=0;j<M;j++) {
            cin>>arr[i][j];
        }
    }

    for (int i=0;i<N; i++) {
        for (int j=0;j<M;j++) {
            if(arr[i][j]&&!visited[i][j]){
                island++;
                initIsland(i,j);
            }
        }
    }
    for (int i=0;i<=island; i++) {
        for (int j=0;j<=island;j++) {
            edge[i][j]=INF;
        }
    }
    for (int i=0;i<N; i++) {
        for (int j=0;j<M;j++) {
            if(arr[i][j]){
                findWay(i,j);
            }
        }
    }
    infopq pq;
    for (int i=0;i<=island; i++) {
        for (int j=i+1;j<=island;j++) {
            if(edge[i][j]!=INF){
                pq.push({edge[i][j],{i,j}});
            }
        }
    }
    cout<<ans(pq);
}
//######################################

void initIsland(int i,int j){
    queue<p> q;
    visited[i][j]=true;
    q.push({i,j});
    while(!q.empty()){
        int cx=q.front().first;
        int cy=q.front().second;
        arr[cx][cy]=island;
        q.pop();
        for(int d=0;d<4;d++){
            int nx=cx+dx[d];
            int ny=cy+dy[d];
            if(!rangeCheck(nx, ny))
                continue;
            if(visited[nx][ny]==false&&arr[nx][ny]){
                visited[nx][ny]=true;
                q.push({nx,ny});
            }
        }
    }
}
void findWay(int i,int j){
    for(int k=0;k<4;k++){
        int cx=i+dx[k];
        int cy=j+dy[k];
        int cnt=0;
        while(rangeCheck(cx, cy)&&!arr[cx][cy]){
            cx+=dx[k];
            cy+=dy[k];
            cnt++;
        }
        if(!rangeCheck(cx, cy)||arr[cx][cy]==arr[i][j]||cnt<2)
            continue;
        else
            edge[arr[i][j]][arr[cx][cy]]=min(edge[arr[i][j]][arr[cx][cy]],cnt);
    }
}
bool findCycle(int s,vector<vector<int>> table){
    queue<int> q;
    q.push(s);
    vector<bool> vs(island+1);
    vs[s]=true;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=1;i<=island;i++){
            if(i!=cur&&table[cur][i]){
                if(vs[i]) return true;
                table[cur][i]=table[i][cur]=0;//**양방향일경우에 간선하나를 사이클로 인지하게 되므로 , 한번쓴 간선은 버린다.
                q.push(i);
                vs[i]=true;
            }
        }
    }
    return false;
}
int ans(infopq q){
    vector<vector<int>> temp(island+1);
    for(int i=1;i<=island;i++)
        temp[i].resize(island+1);
    int cnt=0;
    int ret=0;
    while(!q.empty()&&cnt!=(island-1)){
        int s=q.top().second.first;
        int e=q.top().second.second;
        int dist=q.top().first;
        q.pop();
        temp[s][e]=temp[e][s]=dist;
        if(findCycle(s,temp)){
            temp[s][e]=temp[e][s]=0;
        }else{//사이클이 없으면
            ret+=dist;
            cnt++;
        }
    }
    return (cnt==island-1?ret:-1);
}
