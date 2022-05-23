#include <iostream>
#include <queue>
#include<cstring>
#include<vector>
#define MAX_L 50
#define NONE 0
#define WALL 1
#define WATER 2
#define SET_SIZE (1<<12)-1
using namespace std;
struct p{
    int x;
    int y;
};

int N,M;
string field[MAX_L];
int par[SET_SIZE]={};
int parH[SET_SIZE]={};
int stt[MAX_L][MAX_L];
bool visited[MAX_L][MAX_L];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool check(int x,int y){
    return (0 <= x && x < N && 0 <= y && y < M);
}
int p2i(int x,int y){
    return (x<<6)+y;
}
void checkWatable(int i, int j);
int find(int x){
    if(x==par[x]) return par[x];
    return par[x] = find(par[x]);
}

void merge(int x,int y){
    int px = find(x);
    int py = find(y);
    if(px==py) return ;
    int val = min(parH[px], parH[py]);
    par[px]=py;
    parH[py]=val;
}


int main(){
    cin>>N>>M;
    for (int i = 0; i < N; ++i) {
        cin >> field[i];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {

            if(stt[i][j]==NONE){
                memset(visited, 0, sizeof(visited));
                checkWatable(i,j);
            }
        }
    }
    for (int i = 0; i < SET_SIZE; ++i) {
        par[i] = i;
    }
    memset(parH, 0x3f, sizeof(parH));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (stt[i][j] == WATER) {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (check(ni, nj)) {
                        if (stt[ni][nj] == WATER) {
                            merge(p2i(ni, nj), p2i(i, j));
                        }else{
                            int px = find(p2i(i, j));
                            parH[px] = min(parH[px], field[ni][nj] - '0');
                        }
                    }
                }
            }
        }
    }
    int ret=0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if(stt[i][j]==WATER) {
                ret += (parH[find(p2i(i, j))]-(field[i][j] - '0'));
            }
        }
    }
    cout<<ret;
}
vector<p> visitedP;


void checkWatable(int i,int j){
    visitedP={};
    queue<p> q;
    bool flg=true;
    visited[i][j]=true;
    q.push({i, j});
    int startH=field[i][j]-'0';
    while(!q.empty()){
        int cx=q.front().x;
        int cy=q.front().y;
        if (cx == 0 || cx == N - 1 || cy == 0 || cy == M - 1) {
            flg=false;
        }
        visitedP.push_back(q.front());
        q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = cx + dx[k];
            int ny = cy + dy[k];
            if(check(nx,ny)&&!visited[nx][ny]&&(startH>=(field[nx][ny]-'0'))){
                visited[nx][ny]=true;
                q.push({nx, ny});
            }
        }
    }
    for (auto el:visitedP) {
        int x=el.x;
        int y=el.y;
        int h=(field[x][y] - '0');
        if (h == startH) {
            stt[x][y] = (flg ? WATER : WALL);
        } else {
            if (!flg) {
                visited[x][y] = false;
            } else {
                stt[x][y] = WATER;
            }
        }
    }
}