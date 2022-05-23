//
//  21610.cpp
//  boj
// 배열에서 대각선 이동 , 환형일때 이동하는것 구현
//  Created by 윤태성 on 2021/07/23.
//16:45``

#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
using namespace std;
typedef pair<int,int> p;

int N,M;//1,3,4,8
int dx[]={0,0,-1,-1,-1,0,1,1,1};
int dy[]={0,-1,-1,0,1,1,1,0,-1};
int arr[51][51]={};
int check[51][51]={};
int cd[100]={};
int cs[100]={};
vector<p> grm;
void copyWater(){
    int sq[]={2,4,6,8};
    for(int i=1;i<=N;i++){
        for (int j=1; j<=N; j++) {
            int cnt=0;
            if(!check[i][j]) continue;
            for(int k=0;k<4;k++){
                int cx=i+dx[sq[k]];
                int cy=j+dy[sq[k]];
                if(1<=cx&&cx<=N&&1<=cy&&cy<=N&&arr[cx][cy]){
                    cnt++;
                }
            }
            arr[i][j]+=cnt;
        }
    }
    
}
void moveGrm(int d,int s){
    //cout<<d<<" "<<s<<endl;
    for(int i=0;i<grm.size();i++){
        //cout<<grm[i].first<<" "<<grm[i].second;
        int temps=s;
        while(temps--){
            grm[i].first=(grm[i].first+dx[d])%N;
            grm[i].second=(grm[i].second+dy[d])%N;
            grm[i].first=(grm[i].first?grm[i].first:N);
            grm[i].second=(grm[i].second?grm[i].second:N);
        }
        //cout<<"-->"<<grm[i].first<<" "<<grm[i].second<<endl;
        arr[grm[i].first][grm[i].second]++;
        check[grm[i].first][grm[i].second]=true;
    }
    while(grm.size()){
        grm.pop_back();
    }
    copyWater();
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(!check[i][j]&&arr[i][j]>=2){
                grm.push_back({i,j});
                arr[i][j]-=2;
            }
        }
    }
    memset(check,0,sizeof(check));
}
int main(){
    cin>>N>>M;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            cin>>arr[i][j];
        }
    }
    grm.push_back({N-1,1});
    grm.push_back({N-1,2});
    grm.push_back({N,1});
    grm.push_back({N,2});
    //check[N-1][1]=check[N-1][2]=check[N][1]=check[N][2]=1;
    for (int i=0; i<M; i++) {
        cin>>cd[i]>>cs[i];
    }
    for (int i=0; i<M; i++) {
        moveGrm(cd[i],cs[i]);
    }
    int ans=0;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
           ans+=arr[i][j];
        }
    }
    cout<<ans;
}
