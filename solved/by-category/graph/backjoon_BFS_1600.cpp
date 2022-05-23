//−1,969,100
//−1,947,812
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> p;
typedef pair<p,p> node;
int K,W,H;
bool visited[200][200][31]={};
int trip[200][200]={};
int mx[]={1,-1,0,0};
int my[]={0,0,1,-1};
int hx[]={-2,-2,-1,-1,1,1,2,2};
int hy[]={1,-1,2,-2,2,-2,1,-1};
bool check(int x,int y){
	return (0<=x&&x<H&&0<=y&&y<W)&&(!trip[x][y]);
}
int bfs(){
	queue<node> q;
	q.push({{0,0},{0,K}});
	visited[0][0][K]=true;
	while(!q.empty()){
		int cx=q.front().first.first;
		int cy=q.front().first.second;
		int dstc=q.front().second.first;
		int ck=q.front().second.second;
		q.pop();
		if(cx==H-1&&cy==W-1) return dstc;
		if(ck>0){
			for(int x=0;x<8;x++){
				int nx=cx+hx[x];
				int ny=cy+hy[x];
				if(check(nx,ny)&&!visited[nx][ny][ck-1]){
					visited[nx][ny][ck-1]=true;
					q.push({{nx,ny},{dstc+1,ck-1}});
				}
			}
		}
		for(int x=0;x<4;x++){
			int nx=cx+mx[x];
			int ny=cy+my[x];
			if(check(nx,ny)&&!visited[nx][ny][ck]){
				visited[nx][ny][ck]=true;
				q.push({{nx,ny},{dstc+1,ck}});
			}
		}
		
	}
	return -1;
}
int main(){
	cin>>K>>W>>H;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			cin>>trip[i][j];
		}
	}
	int ans=bfs();
	cout<<ans;
}