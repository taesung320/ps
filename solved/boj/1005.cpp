//
// Created by 윤태성 on 2021/12/11.
//
//TODO : ACM 크래프트 , 위상정렬로 풀어보기
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int N,K,W;
vector<vector<int>> edge;
vector<int> tm;
int cache[1001] = {};
int dp(int x){
    int& ret=cache[x];
    if(edge[x].size()==0) return ret=tm[x];
    if(ret!=-1) return ret;
    ret=0;
    for (int i = 0; i < edge[x].size(); ++i) {
        int pre=edge[x][i];
        ret=max(dp(pre)+tm[x],ret);
    }
    return ret;
}
int main(){
    int T;
    cin>>T;

    while (T--) {
        cin>>N>>K;
        int pre,post;
        memset(cache, -1, sizeof(cache));
        tm.clear();
        tm.resize(N + 1);
        edge.clear();
        edge.resize(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin>>tm[i];
        }
        for (int i = 0; i < K; ++i) {
            cin>>pre>>post;
            edge[post].push_back(pre);
        }
        cin>>W;
        int ans=dp(W);
        cout << ans << '\n';
    }

}