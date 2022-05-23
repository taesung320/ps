//
// Created by 윤태성 on 2022/01/09.
//

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,int> node;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
const char BOMBED='#';
bool visited[12][6]={};
string field[12]={};
inline bool check(int x,int y){
    return (0 <= x && x < 12 && 0 <= y && y < 12);
}
void printField(){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout<<field[i][j]<<" ";
        }
        cout<<endl;
    }
}
inline void fallDown(){
    // printField();
    for (int j = 0; j <6 ; ++j) {
        for (int i = 11; i >=0; --i) {
            if(field[i][j]!='.'){
                int ci=i;
                while(check(ci+1,j)&&field[ci+1][j]=='.'){
                    ci++;
                }
                if(ci==i) continue;
                field[ci][j]=field[i][j];
                field[i][j]='.';
            }
        }
    }
//    cout<<"-----------\n";
//    printField();
}
bool bfs(int x,int y){
    queue<p> q;
    q.push({x,y});
    visited[x][y]= true;
    char STD=field[x][y];
    vector<p> record;
    while (!q.empty()) {
        int cx=q.front().first;
        int cy=q.front().second;
        record.push_back(q.front());
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx=cx+dx[i];
            int ny=cy+dy[i];
            if(check(nx,ny)&&!visited[nx][ny]&&field[nx][ny]==STD){
                q.push({nx,ny});
                visited[nx][ny]=true;
            }
        }
    }
    if(record.size()>=4){
        for (int i = 0; i <record.size() ; ++i) {
            p c=record[i];
            field[c.first][c.second]='.';
        }
    }
    return (record.size()>=4);
}
int main(){
    for (int i = 0; i < 12; ++i) {
        cin>>field[i];
    }
    int ans=0;
    bool keepGoing=false;
    do{
        keepGoing=false;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 6; ++j) {
                if(!visited[i][j]&&field[i][j]!='.'){
                    bool result=bfs(i,j);
                    if(result){
                        keepGoing=true;
                    }
                }
            }
        }
        int x;
        cin>> x;
        fallDown();
        ans++;
    }while(keepGoing);
    cout<<ans-1;
}

