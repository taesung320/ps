//
// Created by 윤태성 on 2022/01/04.
//


#include<iostream>
#include<string>
#include<vector>
using namespace std;
int dp[1001][1001]={};
int mp[1001][1001]={};
//vector<string> mp;
int N,M;
bool check(int n,int m){
    return (0 <= n && n < N && 0 <= m && m < M);
}
int main() {
    cin>>N>>M;
    for (int i = 1; i <= N; ++i) {
        string s;
        cin>>s;
        // mp.push_back(s);
        for (int j = 0; j < s.size(); ++j) {
            mp[i][j+1]=s[j];
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if(mp[i][j]=='0') continue;
            dp[i][j]=1;
            int comm = min(dp[i-1][j], dp[i][j-1]);
            if(mp[i-comm][j-comm]=='1'){
                dp[i][j]=comm+1;
            }else{
                //  dp[i][j]=comm;
            }
        }
    }
    int ans=0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            ans=max(ans,dp[i][j]);
        }
    }
    cout<<ans*ans;
}

