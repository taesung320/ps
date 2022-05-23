#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
typedef pair<int,int> p;
const int L=101;
const int D=4;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
vector<p> btn[L][L];
set<p> ready_push;
bool is_on[L][L];
bool visited[L][L];
int N,M;
bool check(int x,int y){
    return (1<=x&&x<=N)&&(1<=y&&y<=N);
}
int find_ans(){
    int ret=0;
    is_on[1][1]=true;
    visited[1][1]=true;
    queue<p> que;
    que.push({1,1});
    while (!que.empty()) {

        int curx=que.front().first;
        int cury=que.front().second;
        //cout<<"here:: "<<curx<<" , "<<cury<<endl;
        ret++;
        que.pop();
        //q불키고
        for (int i = 0; i < btn[curx][cury].size(); ++i) {
            p next=btn[curx][cury][i];
            int nx=next.first;
            int ny=next.second;
            is_on[nx][ny]=true;
            //켜저서 갈수있으면 푸시해줌
            if (ready_push.find(next) != ready_push.end()) {
                if(visited[nx][ny]==false){
                    visited[nx][ny]=true;
                    que.push(next);
                }
            }
        }
        for (int i = 0; i < D; ++i) {
            int nx=curx+dx[i];
            int ny=cury+dy[i];
            if(check(nx,ny)==false)continue;

            if(visited[nx][ny]==false){
                if(is_on[nx][ny]==true){
                    //진행
                    visited[nx][ny]=true;
                    que.push({nx, ny});
                }else{
                    //다음을 기약..
                    if (ready_push.find({nx, ny}) == ready_push.end()) {
                        ready_push.insert({nx, ny});
                    }
                }
            }
        }
    }
    return ret;
}
int main(){
    cin>>N>>M;
    for (int i = 0; i < M; ++i) {
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        btn[a][b].push_back({x, y});
    }
    int ans=find_ans();
    int ans2=0;
    for (int i = 0; i < N + 1; ++i) {
        for (int j = 0; j < N + 1; ++j) {
            if(is_on[i][j])
                ans2++;
        }
    }
    cout<< ans2++;
}