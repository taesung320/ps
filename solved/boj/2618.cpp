//
// Created by 윤태성 on 2022/01/04.
//

#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef pair<int,int> p;
int dp[1002][2][1002]={};//[차량위치][차량] [차량위치(사건번호)]
vector<int> dpRoute[1002][2][1002]={};
p w[1002]={};
int N,W;
const int INF=1e9;
int dist(int w1,int w2){
    return abs(w[w1].first-w[w2].first)+abs(w[w1].second-w[w2].second);
}
int main(){
    cin>>N>>W;
    w[0]={1,1};
    w[1]={N,N};
    for (int i = 2; i <= W+1; ++i) {
        cin>>w[i].first>>w[i].second;
    }
    for (int i = 0; i < 1002; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 1002; ++k) {
                dp[i][j][k]=INF;
            }
        }
    }
    dp[0][0][1]=0;
    dp[1][1][0]=0;
    dp[1][1][2] = dist(0, 2);
    dpRoute[1][1][2].push_back(0);
    dp[0][0][2] = dist(1, 2);
    dpRoute[0][0][2].push_back(1);
    for (int i = 2; i <= W; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < 2; ++k) {
                vector<int> curR=dpRoute[j][k][i];
                if(dp[j][k][i]<INF){
                    int temp1=dp[j][k][i]+dist(i,i+1);
                    if(dp[j][k][i+1]>temp1){
                        dp[j][k][i+1]=temp1;
                        dpRoute[j][k][i+1]=curR;
                        dpRoute[j][k][i+1].push_back(!k);
                    }
                    int temp2=dp[j][k][i]+dist(j,i+1);
                    if(dp[i][!k][i+1]>temp2){
                        dp[i][!k][i+1]=temp2;
                        dpRoute[i][!k][i+1]=curR;
                        dpRoute[i][!k][i+1].push_back(k);
                    }

                }
                vector<int>().swap(dpRoute[j][k][i]);//TODO vector 메모리 해제 (capacity 까지 없에줘야함)
            }
        }
    }
    int ans=INF;
    int ansi=0;
    int ansj=0;
    for (int i = 0; i <=W; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(ans>dp[i][j][W+1]){
                ans=dp[i][j][W+1];
                ansi=i;
                ansj=j;
            }
        }
    }
    cout<<ans<<endl;
    for (int i = 0; i < dpRoute[ansi][ansj][W + 1].size(); ++i) {
        cout<<dpRoute[ansi][ansj][W + 1][i]+1<<"\n";
    }
}

