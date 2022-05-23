//
// Created by 윤태성 on 2022/01/28.
//

#define QUEUE_SIZE 200
#define MAP_MAX 10
#include<iostream>
using namespace std;
int board[MAP_MAX][MAP_MAX];
bool visited[MAP_MAX][MAP_MAX];
int mSize;
struct node{
    int r=0;
    int c=0;
    int cnt=0;
    node(int _r=0,int _c=0,int _cnt=0):r(_r),c(_c),cnt(_cnt){}
};
node queue[QUEUE_SIZE];
int q_front=0;
int q_rear=0;
int q_size=0;
node getFront(){
    return queue[q_front];
}
void enqueue(int r,int c,int cnt){
    if(q_size>=QUEUE_SIZE) return;
    q_size++;
    queue[q_rear] = node(r, c,cnt);
    q_rear=(q_rear+1)%QUEUE_SIZE;
}
void deque(){
    if(q_size==0) return;
    queue[q_front] = node();
    q_size--;
    q_front=(q_front+1)%QUEUE_SIZE;
}
void initQueue(){
    for (int i = 0; i < QUEUE_SIZE; ++i) {
        queue[i]=node();
    }
    q_front=q_rear=q_size=0;
}
void bfs_init(int map_size, int map[10][10]) {
    mSize = map_size;
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            board[i][j]=map[i][j];
        }
    }
}
void printQ(){

}
int dr[]={0,0,1,-1};
int dc[]={1,-1,0,0};
int bfs(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < MAP_MAX; ++i) {
        for (int j = 0; j < MAP_MAX; ++j) {
            visited[i][j]=false;
        }
    }
    int ans=-1;
    //bfs -->x는 열이고 y는 행임을 주의해야 한다. 그리고 좌상 좌표는 x=1, y=1 이다.
    initQueue();

    int sr=y1-1;
    int sc=x1-1;
    int er=y2-1;
    int ec=x2-1;

    visited[sr][sc]=true;
    enqueue(sr,sc,0);
    while(q_size>0){
        int cr=getFront().r;
        int cc=getFront().c;
        int cnt=getFront().cnt;
        deque();
        if(cr==er&&cc==ec) return cnt;
        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            if (0 <= nr && nr < mSize && 0 <= nc && nc < mSize) {
                if(visited[nr][nc]) continue;
                if(board[nr][nc]) continue;
                visited[nr][nc]=true;
                enqueue(nr,nc,cnt+1);
            }
        }
    }

    return ans;
}