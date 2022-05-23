//
// Created by 윤태성 on 2022/01/06.
//

#include<iostream>
#include<cstring>
using namespace std;
int p[100000]={};
int dp[5][5][100001]={};
int N=0;
int dist(int a,int b){
    if(a==b) return 1;
    if(a==0||b==0) return 2;
    if(abs(a-b)==2) return 4;
    return 3;
}
int main(){
    int x=-1;
    while(x){
        cin>>x;
        p[++N]=x;
    }
    //TODO int arr init with INF ( memset 은 1byte단위로 메모리를 초기화하므로 1byte길이에 해당하는 값을 넣어야한다)
    const int INF=0x7f7f7f7f;
    cout<<INF<<endl;
    memset(dp,0x7f,sizeof(dp));
    dp[0][0][0]=0;
    for (int i = 1; i < N; ++i) {
        for (int l = 0; l < 5; ++l) {
            for (int r = 0; r < 5; ++r) {
                if(dp[l][r][i-1]<INF){
                    dp[l][p[i]][i] = min(dp[l][p[i]][i], dp[l][r][i - 1] + dist(r, p[i]));
                    dp[p[i]][r][i] = min(dp[p[i]][r][i], dp[l][r][i - 1] + dist(l, p[i]));
                }
            }
        }
    }
    int ans=INF;
    for (int l = 0; l < 5; ++l) {
        for (int r = 0; r < 5; ++r) {
            ans=min(ans,dp[l][r][N-1]);
        }
    }
    cout<<ans;
}
