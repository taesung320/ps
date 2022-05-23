//
// Created by 윤태성 on 2021/11/30.
//

#include<iostream>
#include<vector>
using namespace std;
const int HAS_TEAM=1;
const int NOT_YET=0;
const int FAIL_TEAM=-1;
vector<int> v;
vector<int> has_team;
vector<bool> visited;
vector<int> par;
void init(int N){
    has_team.clear();
    has_team.resize(N + 1);
    visited.clear();
    visited.resize(N+1);
    v.clear();
    v.resize(N+1);
    par.clear();
    par.resize(N+1);
    for (int i = 0; i < par.size(); ++i) {
        par[i]=i;
    }
}
int find(int x){
    if(par[x]==x) return x;
    return par[x]=find(par[x]);
}
bool merge(int x,int y){
    int px = find(x);
    int py = find(y);
    if(px==py) return 0;//merge 안됐음을 리턴
    par[py]=px;
    has_team[py]=has_team[px];
    return 1;
}
void dfs_make_team(int num){
    int next=v[num];
    if(num==next){
        has_team[num]=HAS_TEAM;
        return;
    }else if(v[next]==num){
        visited[next]=true;
        merge(num,next);
        has_team[find(num)]=HAS_TEAM;
    }
    if(visited[next]==false){
        visited[next]=true;
        dfs_make_team(next);
        if(has_team[find(next)]==HAS_TEAM||has_team[find(next)]==FAIL_TEAM) {
            has_team[num] = FAIL_TEAM;
            return;
        }else{
            bool result = merge(num, next);
            if(result==false) {
                has_team[find(num)]=HAS_TEAM;
            }
        }
    }else{
        if(has_team[find(next)]==NOT_YET){
            merge(num, next);
        }else if(has_team[find(num)]!=HAS_TEAM){
            // cout<<num<<" fail to make team"<<endl;
            has_team[num]=FAIL_TEAM;
            return;
        }
    }
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin>>T;
    while (T--) {
        int N;
        cin>>N;
        init(N);
        for (int i = 1; i <= N; ++i) {
            cin>>v[i];
        }
        for (int i = 1; i <=N; ++i) {
            if(visited[i]==false){
                visited[i]=true;
                dfs_make_team(i);
            }
        }
        int ans=0;
        for (int i = 1; i <=N; ++i) {
            if(has_team[find(i)]==HAS_TEAM){
                //  cout<<i<<" - "<<find(i)<<"'"<<endl;
                ans++;
            }
        }
        cout<<N-ans<<"\n";
    }
}
