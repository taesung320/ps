//
//  2146.cpp
//  boj
//
//  Created by 윤태성 on 2021/07/19.
//

#include<iostream>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,int> node;
int N;
int island=0;
int arr[100][100]={};
bool visited[100][100]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool rCheck(int i,int j){
    return (0<=i&&i<N&&0<=j&&j<N);
}
void initIsland(int i,int j);
int findLand(int i,int j);
int main(){
    cin>>N;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin>>arr[i][j];
        }
    }
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if(visited[i][j]||!arr[i][j]) continue;
            island++;
            initIsland(i,j);
        }
    }
    
    int ans=1e9;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if(arr[i][j])
            ans=min(ans,findLand(i,j));
        }
    }
    cout<<ans;
}

void initIsland(int i,int j){
    queue<p> q;
    q.push({i,j});
    visited[i][j]=true;
    while(!q.empty()){
        int cx=q.front().first;
        int cy=q.front().second;
        arr[cx][cy]=island;
        q.pop();
        for(int k=0;k<4;k++){
            int nx=cx+dx[k];
            int ny=cy+dy[k];
            if(rCheck(nx,ny)&&arr[nx][ny]&&!visited[nx][ny]){
                q.push({nx,ny});
                visited[nx][ny]=true;
            }
        }
    }
}

int findLand(int i,int j){
    vector<vector<bool>> vstd(N);
    for(int i=0;i<N;i++)
        vstd[i].resize(N);
    queue<node> q;
    q.push({{i,j},-1});
    vstd[i][j]=true;
    while(!q.empty()){
        int cx=q.front().first.first;
        int cy=q.front().first.second;
        int cnt=q.front().second;
        q.pop();
        for (int k=0; k<4; k++) {
            int nx=cx+dx[k];
            int ny=cy+dy[k];
            if(!rCheck(nx, ny)||arr[nx][ny]==arr[i][j]) continue;
            if(!arr[nx][ny]&&vstd[nx][ny]==false){
                q.push({{nx,ny},cnt+1});
                vstd[nx][ny]=true;
            }else if(arr[nx][ny]&&arr[nx][ny]!=arr[i][j]){
                return cnt+1;
            }
        }
    }
    return 1e9;
}
