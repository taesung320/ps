//
// Created by 윤태성 on 2021/12/11.
//


#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef pair<int,int> p;
vector<string> field;
int N,M;
int par[10011001]={};
bool visited[1001][1001]={};
bool ans_par[10011001]={};
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
char dc[]={'U','D','L','R'};
int getDx(char c){
    for (int i = 0; i < 4; ++i) {
        if(c==dc[i]) return dx[i];
    }
}
int getDy(char c){
    for (int i = 0; i < 4; ++i) {
        if(c==dc[i]) return dy[i];
    }
}
int ij2idx(p ij){
    return (ij.first*10000+ij.second);
}
p idx2ij(int idx){
    return {idx / 10000, idx % 10000};
}
int find(p ij){
    int idx=ij2idx({ij.first,ij.second});
    if(par[idx]== idx) return idx;
    return par[idx]=find(idx2ij(par[idx]));
}
void merge(p p1, p p2){
    int par1=find(p1);
    int par2=find(p2);
    if (par1 != par2) {
        par[par1]=par2;
    }
}
bool check(int i,int j){
    return (0 <= i && i < N && 0 <= j && j < M);
}
void dfs(int i,int j){
    visited[i][j]=true;
    char cur=field[i][j];
    int ni=i+ getDx(cur);
    int nj=j+ getDy(cur);
    if (check(ni, nj)) {
        visited[ni][nj]=true;
        merge({i,j},{ni,nj});
        if(visited[ni][nj]==false)
            dfs(ni,nj);
    }
}
int main(){
    cin>>N>>M;
    field.resize(N);
    for (int i = 0; i <10011001; ++i) {
        par[i]=i;
    }
    for (int i = 0; i < N; ++i) {
        cin>>field[i];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            dfs(i,j);
        }
    }
    int ans=0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if(ans_par[find({i,j})]==false){
                ans_par[find({i,j})]=true;
                ans++;
            }
        }
    }
    cout<<ans;
}