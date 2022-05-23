//
// Created by 윤태성 on 2022/04/04.
//

#include<vector>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<string>
#define MAXL 102
using namespace std;
struct p{
    int r;
    int c;
    p(int _r=0,int _c=0):r(_r),c(_c){}
};
bool comp(const p p1, const p p2){
    if(p1.c!=p2.c) return p1.c<p2.c;
    if(p1.r!=p2.r)return p1.r>p2.r;//바닥에 가까운게 더 먼저나옴
    return true;
}
int R,C;
int dr[] = {0, 0, -1, 1};
int dc[] = {1, -1, 0, 0};
string field[MAXL];
bool check(int r,int c){
    return (1 <= r && r <= R && 0 <= c && c < C);
}
vector<p> toFall;
vector<p> temp;
queue<p> q;

bool visited[MAXL][MAXL];
void checkFall(int r,int c){
    temp = {};
    q = {};
    q.push({r, c});
    visited[r][c]=true;
    while (!q.empty()) {
        int cr = q.front().r;
        int cc = q.front().c;
        q.pop();
        temp.emplace_back(cr,cc);
        if(cr==R){
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            if(check(nr,nc)&&field[nr][nc]=='x'&&!visited[nr][nc]){
                q.push({nr, nc});
                visited[nr][nc]=true;
            }
        }
    }
    toFall=temp;
}
void fallMineral(){
    if(!toFall.empty()){
        sort(toFall.begin(), toFall.end(), comp);
        int minFallHeight=1e9;
        for (p el:toFall) {
            // cout<<el.r<<" "<<el.c<<endl;
            int row=el.r;
            int col=el.c;
            if (check(row+1,col)&&field[row + 1][col] == '.') {
                int cnt=0;
                while (check(row+1, col) && field[row + 1][col] == '.') {
                    row++;
                    cnt++;
                }
                if(!check(row+1,col)||!visited[row+1][col])
                    minFallHeight = min(cnt, minFallHeight);
            }
        }
        for (p el: toFall) {
            field[el.r+minFallHeight][el.c]='x';
            field[el.r][el.c]='.';
        }
    }
}
void throwStick(int r,int c,bool isLeft){
    int cr=r;
    int cc=c;
    int offset = (isLeft ? 1 : -1);
    while(0<=cc&&cc<C&&field[cr][cc]!='x'){
        cc+=offset;
    }
    if(0<=cc&&cc<C){
        field[cr][cc]='.';
    }else{
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int nr = cr + dr[i];
        int nc = cc + dc[i];
        memset(visited, 0, sizeof(visited));
        if (check(nr, nc) && field[nr][nc] == 'x'&&!visited[nr][nc]) {
            toFall = {};
            checkFall(nr,nc);
            fallMineral();
            if(!toFall.empty())
                break;
        }
    }
}
void printField(){
    for (int i = 1; i <= R; ++i) {
        cout<<field[i]<<"\n";
    }
}
int main(){
    cin>>R>>C;
    for (int i = 1; i <= R; ++i) {
        cin >> field[i];
    }
    int N;
    cin>>N;
    bool isLeft=true;
    while (N--) {
        int h;
        cin>>h;
        if(h>R) continue;
        if(isLeft){
            throwStick(R - h + 1, 0, isLeft);
        }else{
            throwStick(R - h + 1, C-1, isLeft);
        }

        isLeft = !isLeft;
    }
    printField();
    return 0;
}
