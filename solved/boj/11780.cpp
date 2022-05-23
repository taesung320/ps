//
// Created by 윤태성 on 2021/12/13.
//

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int INF=1e9;
int N,M;
int edge[101][101]={};
vector<int> route[101][101]={};
vector<int> merge(vector<int> pre,vector<int> post){
    vector<int> ret=pre;
    for (int i = 1; i <post.size() ; ++i) {
        ret.push_back(post[i]);
    }
    return ret;
}
int main(){
    cin>>N>>M;
    memset(edge,INF,sizeof(edge));// 이게되나?
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            edge[i][j]=INF;
        }
        cout<<"\n";
    }
    for (int i = 0; i < M; ++i) {
        int a,b,c;
        cin>>a>>b>>c;
        edge[a][b]=min(edge[a][b],c);
        route[a][b]={a,b};// 이게되나?
    }
    for (int k = 1; k <=N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if(i==j) continue;
                int temp=edge[i][k]+edge[k][j];
                if(edge[i][j]>temp){
                    edge[i][j]=temp;
                    route[i][j]=merge(route[i][k],route[k][j]);
                }
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cout<<(edge[i][j]>=INF?0:edge[i][j])<<" ";
        }
        cout<<endl;
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if(route[i][j].size()){
                cout<<route[i][j].size()<<" ";
                for (int k = 0; k < route[i][j].size(); ++k) {
                    cout<<route[i][j][k]<<" ";
                }
                cout<<'\n';
            }else{
                cout<<"0\n";
            }
        }
    }
}