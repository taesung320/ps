//
// Created by 윤태성 on 2022/05/16.
//

#include <iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
int H,W;
vector<string> field;
bool check(int r,int c){
    return (0 <= r && r < H && 0 <= c && c < W);
}
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
int cost[4][100][100];
struct node{
    int r,c,dir;
};
int findWay(int r,int c){
    memset(cost, 0x3f, sizeof(cost));
    queue<node> q;
    int ret=0x3f3f3f3f;
    for (int i = 0; i < 4; ++i) {
        cost[i][r][c]=0;
        q.push({r, c, i});
    }
    field[r][c]='c';
    while (!q.empty()) {
        node curNode=q.front();
        int curCost=cost[curNode.dir][curNode.r][curNode.c];
        q.pop();
        if(field[curNode.r][curNode.c]=='C'){
            ret=min(ret,curCost);
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int nr = curNode.r + dr[i];
            int nc = curNode.c + dc[i];
            if(!check(nr,nc)||(field[nr][nc]=='*')) continue;
            if((i/2==curNode.dir/2)&&(i!=curNode.dir)) continue;
            if(cost[i][nr][nc]>curCost+(curNode.dir!=i)){
                cost[i][nr][nc]=curCost+(curNode.dir!=i);
                q.push({nr, nc, i});
            }
        }
    }
    return ret;
}
int main(){
    cin>>W>>H;
    for (int i = 0; i < H; ++i) {
        string s;
        cin>>s;
        field.push_back(s);
    }
    int ans;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if(field[i][j]=='C'){
                ans= findWay(i,j);
                cout<<ans;
                return 0;
            }
        }
    }
}