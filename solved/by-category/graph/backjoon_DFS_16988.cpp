#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
struct point{
	int x;
	int y;
	point(int _x=0,int _y=0):x(_x),y(_y){};
};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int arr[20][20]={};
bool visited[20][20]={};
bool done[20][20][20][20]={};
int N,M;
int isDead(int x,int y);
int dead2();//arr 를 탐색하여 죽어있는 2의 개수 반환
int main(){
	cin>>N>>M;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
		}
	}
	int ans=0;
	for(int x1=0;x1<N;x1++){
		for(int y1=0;y1<M;y1++){
			if(arr[x1][y1]==0){
				arr[x1][y1]=1;
				for(int x2=0;x2<N;x2++){
					for(int y2=0;y2<M;y2++){
						if(arr[x2][y2]==0){
							arr[x2][y2]=1;
							if(done[x1][y1][x2][y2]){
								continue;
							}else{
								done[x1][y1][x2][y2]=1;
							}
							ans=max(ans,dead2());
							memset(visited,0,sizeof(visited));
							arr[x2][y2]=0;
						}
					}
				}
				arr[x1][y1]=0;
			}
		}
	}
	cout<<ans;
}
int dead2(){
	int ret=0;
	for(int x1=0;x1<N;x1++){
		for(int y1=0;y1<M;y1++){
			if(arr[x1][y1]==2&&!visited[x1][y1]){
				ret+=isDead(x1,y1);
			}
		}
	}
	return ret;
}
int isDead(int x,int y){
	queue<point> q;
	q.push(point(x,y));
	visited[x][y]=true;
	int ret=1;
	int nodead=0;
	while(!q.empty()){
		int curx=q.front().x;
		int cury=q.front().y;
		q.pop();
		for(int k=0;k<4;k++){
			int nx=curx+dx[k];
			int ny=cury+dy[k];
			if(0<=nx&&nx<N&&0<=ny&&ny<M){
			if(arr[nx][ny]!=1&&!visited[nx][ny]){
				if(arr[nx][ny]==0) {
					nodead=1;
				}
				q.push(point(nx,ny));
				ret++;
				visited[nx][ny]=true;
			}
		}
		}
	}
	return (nodead?0:ret);
}