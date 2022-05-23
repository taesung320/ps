//
// Created by 윤태성 on 2021/12/02.
//

#include<iostream>
using namespace std;
int par[500001]={};
//@TODO: 사이클 판별법(유니온 파인드로)
int find(int x){
    if(x==par[x]) return x;
    return par[x]=find(par[x]);
}
bool merge(int x,int y){
    int px = find(x);
    int py = find(y);
    if (px != py) {
        par[py]=px;
        return true;
    }else{
        return false;
    }

}
int main(){
    int N,M;
    cin>>N>>M;
    int ans=0;
    for (int i = 0; i < N; ++i) {
        par[i]=i;
    }
    for (int i = 0; i < M; ++i) {
        int a,b;
        cin>>a>>b;
        bool result = merge(a, b);
        if (!result) {
            ans=i+1;
            break;
        }
    }
    cout<<ans;
}