//
// Created by 윤태성 on 2021/12/28.
//

#include<iostream>
#include<cstring>
//TODO 답보고 푼 문제... dp
using namespace std;
int cost[101] = {};
int memo[101] = {};
int dp[101][10001] = {};
int N,M;
int main(){
    cin>>N>>M;
    for (int i = 1; i <= N; ++i) {
        cin >> memo[i];
    }
    int sum=0;
    for (int i = 1; i <= N; ++i) {
        cin >> cost[i];
        sum+=cost[i];
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <=sum ; ++j) {
            if(j-cost[i]>=0){
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-cost[i]]+memo[i]);
            }
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
    }
    for (int i = 0; i <= sum; ++i) {
        if(dp[N][i]>=M){
            cout<<i;
            break;
        }
    }
}