//
//  20058.cpp
//  boj
//  배열에서 동시에 일어나는일 ( ex. 얼음이 녹는다 ) 처리할때 타겟 변수 한번에 모았다가 한번에 처리
//  동시에 일어나는 일이 다른 개체에 영향을 주면 안됨.
//  Created by 윤태성 on 2021/07/21.
//

#include <stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,int> node;
int N,Q;
int len;
int arr[1<<7][1<<7]={};
bool visited[1<<7][1<<7]={};
int command[1000]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool rangeCheck(int x,int y){
    return (0<=x&&x<len&&0<=y&&y<len);
}
void spinArr(int cx,int cy,int length){
    vector<vector<int>> temp(length);
    for(int i=0;i<length;i++)
        temp[i].resize(length);
    
    for(int i=0;i<length;i++){
        for (int j=0; j<length;j++) {
            temp[j][length-1-i]=arr[cx+i][cy+j];
        }
    }
    for(int i=0;i<length;i++){
        for (int j=0; j<length;j++) {
            arr[cx+i][cy+j]=temp[i][j];
        }
    }
}
void check(){
    vector<p> temp;
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            int cnt=0;
            if(arr[i][j]==0) continue;
            for(int k=0;k<4;k++){
                int cx=i+dx[k];
                int cy=j+dy[k];
                if(!rangeCheck(cx, cy)) continue;
                if(arr[cx][cy]){
                    cnt++;
                }
            }
            if(cnt<3){
                temp.push_back({i,j});
            }
        }
    }
    for(int i=0;i<temp.size();i++){
        int x=temp[i].first;
        int y=temp[i].second;
        if(arr[x][y]) arr[x][y]--;
    }
}
int bfs(int i,int j){
    queue<p> q;
    int ret=0;
    q.push({i,j});
    visited[i][j]=true;
    while(!q.empty()){
        int cx=q.front().first;
        int cy=q.front().second;
        ret++;
        q.pop();
        for(int k=0;k<4;k++){
            int nx=cx+dx[k];
            int ny=cy+dy[k];
            if(rangeCheck(nx, ny)&&arr[nx][ny]&&visited[nx][ny]==false){
                visited[nx][ny]=true;
                q.push({nx,ny});
            }
        }
        
    }
    return ret;
}
int main(){
    cin>>N>>Q;
    len=pow(2,N);
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            cin>>arr[i][j];
        }
    }
    for (int i=0; i<Q; i++) {
        cin>>command[i];
    }
    for(int i=0;i<Q;i++){
        int offset=pow(2,command[i]);
        for (int j=0; j<len; j+=offset) {
            for (int k=0; k<len; k+=offset) {
                spinArr(j,k,offset);
            }
        }
        check();
    }
    int fir_ans=0;
    for (int i=0; i<len; i++) {
        for (int j=0;j<len; j++) {
            fir_ans+=arr[i][j];
        }
    }
    int sec_ans=0;
    for (int i=0; i<len; i++) {
        for (int j=0;j<len; j++) {
            if(arr[i][j]&&visited[i][j]==false)
                sec_ans=max(sec_ans,bfs(i,j));
        }
    }
    cout<<fir_ans<<"\n"<<(sec_ans==1?0:sec_ans);
}
