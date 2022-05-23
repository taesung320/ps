//
// Created by 윤태성 on 2021/12/07.
//

#include<iostream>
#include<cstring>
using namespace std;
typedef pair<int,int> p;
const int INF=1e9;
int N;
int cache[501][501] = {};
p mtrx[501]={};
int dp(int left,int right){
    int &ret = cache[left][right];
    if (ret != -1) return ret;
    if(abs(left-right)==1) return ret=(mtrx[left].first*mtrx[left].second*mtrx[right].second);
    if(left==right) return ret=00;
    ret=INF;
    for (int i = left; i < right; ++i) {
        int result=dp(left,i)+dp(i+1,right)+mtrx[left].first*mtrx[i].second*mtrx[right].second;
        ret=min(ret,result);
    }
    return ret;
}

int main(){
    cin>>N;
    memset(cache, -1, sizeof(cache));
    for (int i = 1; i <= N; ++i) {
        cin>>mtrx[i].first>>mtrx[i].second;
    }
    int ans=dp(1,N);
    cout<<ans;

}