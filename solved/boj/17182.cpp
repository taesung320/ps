//
//  17182.cpp
//  boj
//
//  Created by 윤태성 on 2021/11/24.
//
#include <iostream>
#include <cstring>
using namespace std;
int edge[10][10]={};
int cache[10][1<<10]={};
int N,start;
int INF=1e9;
int markBit(int bit,int i){
    if(bit&(1<<i)){
        return bit;
    }else{
        return bit+(1<<i);
    }
}
bool checkFool(int bit){
    return bit==((1<<N)-1);
}
bool checkBit(int bit,int i){
    return (bit&(1<<i));
}
int dp(int start,int visited){
    if(checkFool(visited)){
        return 0;
    }
    int& ret=cache[start][visited];
    if(ret!=-1) return ret;
    ret=INF;
    for(int i=0;i<N;i++){
        if(start!=i){
            int cost=edge[start][i];
            ret=min(ret,cost+dp(i,markBit(visited, i)));
        }
    }
    return ret;
}
int main(){
    cin>>N>>start;
    for(int i=0;i<N;i++){
        for (int j=0; j<N; j++) {
            cin>>edge[i][j];
        }
    }
    for(int k=0;k<N;k++){
        for (int j=0; j<N; j++) {
            for (int i=0; i<N; i++) {
                edge[i][j]=min(edge[i][j],edge[i][k]+edge[k][j]);
            }
        }
    }
    memset(cache,-1,sizeof(cache));
    int ans=dp(start,markBit(0, start));
    cout<<ans;
}
