#include<iostream>
#include<queue>
#include<string>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,pair<p,bool>> node;
int N,M,K;
string field[1000]={};
bool visited[1000][1000][11][2]={};
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<M);
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int bfs(){
	queue<node> q;
	q.push({{0,0},{{0,1},1}});
	visited[0][0][0][0]=true;
	while(!q.empty()){
		p cur=q.front().first;
		p info=q.front().second.first;
		bool isDay=q.front().second.second;
		int cx=cur.first;
		int cy=cur.second;
		int cn=info.first;
		int dstc=info.second;
		q.pop();
		if(cx==N-1&&cy==M-1)
			return dstc;
		for(int k=0;k<4;k++){
			int nx=cx+dx[k];
			int ny=cy+dy[k];
			bool nday=!isDay;
			if(check(nx,ny)){
				if(field[nx][ny]=='0'&&!visited[nx][ny][cn][nday]){
					//그냥 이동, 낮->밤 / 밤->낮
					visited[nx][ny][cn][nday]=true;
					q.push({{nx,ny},{{cn,dstc+1},nday}});
				}else if(cn<K){
					//벽 부수고 이동
					if(isDay&&!visited[nx][ny][cn+1][nday]){
						//낮에는 그냥 이동
						visited[nx][ny][cn+1][nday]=true;
						q.push({{nx,ny},{{cn+1,dstc+1},nday}});
					}else if(!visited[cx][cy][cn+1][nday]){
						//밤에는 대기
						visited[cx][cy][cn+1][nday]=true;
						q.push({{cx,cy},{{cn,dstc+1},nday}});
					}
				}
			}
		}
	}
	return 0;
}

int main(){
	cin>>N>>M>>K;
	for(int i=0;i<N;i++){
		cin>>field[i];
	}
	int ans=bfs();
	cout<<(ans?ans:-1);
}