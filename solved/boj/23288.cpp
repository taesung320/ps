#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> p;
const int W=3;
const int E=1;
const int S=2;
const int N=0;
int rowDice[]={4,1,3,6};
int colDice[]={2,1,5,6};
int rowOffset=0;
int colOffset=0;
int n,m,K;
int d=1;
int ans=0;
int getRowIdx(int i){
    return (i+rowOffset+4)%4;
}
int getColIdx(int i){
    return (i+colOffset+4)%4;
}
void moveDice(int d){
    if(d==W||d==E){
        rowOffset+=(d==W?1:-1);
        rowOffset=(rowOffset+4)%4;
        colDice[getColIdx(1)]=rowDice[getRowIdx(1)];
        colDice[getColIdx(3)]=rowDice[getRowIdx(3)];
    }else if(d==S||d==N){
        colOffset+=(d==S?-1:1);
        colOffset=(colOffset+4)%4;
        rowDice[getRowIdx(1)]=colDice[getColIdx(1)];
        rowDice[getRowIdx(3)]=colDice[getColIdx(3)];
    }
}
int field[20][20] = {};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
bool check(int x,int y){
    return (0 <= x && x < n && 0 <= y && y < m);
}
void checkScore(int x, int y,int c) {
    cout<<x<<" "<<y<<" ::";
    vector<vector<bool>> visited(n);
    for (int i = 0; i < n; ++i) {
        visited[i].resize(m);
    }
    visited[x][y]=true;
    queue<p> q;
    q.push({x,y});
    int ret=0;
    while (!q.empty()) {
        int cx=q.front().first;
        int cy=q.front().second;
        q.pop();
        ret+=c;
        for (int i = 0; i <4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (check(nx,ny)&&field[nx][ny]==c&&!visited[nx][ny]) {
                visited[nx][ny]=true;
                q.push({nx,ny});
            }
        }
    }
    ans+=ret;
    cout<<ret<<endl;
}
void reverse_dir(){
    d=(d==0?2:(d==1?3:(d==2?0:(d==3?1:0))));
}

int main(){
    cin>>n>>m>>K;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>field[i][j];
        }
    }
    int cx=0;
    int cy=0;
    for (int i = 0; i < K; ++i) {
        int nx=cx+dx[d];
        int ny=cy+dy[d];
        if(!check(nx,ny)){
            reverse_dir();
            nx=cx+dx[d];
            ny=cy+dy[d];
        }
        // cout<<"d::"<<d<<endl;
        moveDice(d);
        cx=nx;
        cy=ny;
        int next_s = field[nx][ny];
        checkScore(nx,ny,next_s);
        int lower=rowDice[getRowIdx(3)];
        if (lower > next_s) {
            d++;
            d=d%4;
        } else if (lower< next_s) {
            d--;
            d=(d+4)%4;
        }
    }
    cout<<rowDice[getRowIdx(3)]<<endl;
    cout<<ans<<endl;
}
