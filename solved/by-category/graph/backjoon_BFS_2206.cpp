#include<iostream>
#include<queue>
#include<string>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,p> node;
int N,M;
string field[1000]={};
bool visited[1000][1000][2]={};
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<M);
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int bfs(){
	queue<node> q;
	q.push({{0,0},{0,1}});
	visited[0][0][0]=true;
	while(!q.empty()){
		p cur=q.front().first;
		p info=q.front().second;
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
			if(check(nx,ny)){
				if(field[nx][ny]=='0'&&!visited[nx][ny][cn]){
					visited[nx][ny][cn]=true;
					q.push({{nx,ny},{cn,dstc+1}});
				}else if(cn==0&&!visited[nx][ny][1]){
					visited[nx][ny][1]=true;
					q.push({{nx,ny},{1,dstc+1}});
				}
			}
		}
	}
	return 0;
}

int main(){
	cin>>N>>M;
	for(int i=0;i<N;i++){
		cin>>field[i];
	}
	int ans=bfs();
	cout<<(ans?ans:-1);
}