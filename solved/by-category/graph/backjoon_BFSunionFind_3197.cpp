#include<iostream>
#include<utility>
#include<queue>
#include<string>
using namespace std;
typedef pair<int,int> p;
int xy2i(int x,int y){
	return 10000*x+y;
}
int xy2i(p pnt){
	return xy2i(pnt.first,pnt.second);
}
p i2xy(int i){
	return {i/10000,i%10000}; 
}
const int len=20000000;
int par[len]={};
int wday[len]={};
int find(int x){
	if(par[x]==x) return x;
	else return par[x]=find(par[x]);
}
void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx==fy) return;
	par[fy]=fx;
}
int R,C;
string hosu[1500]={};
bool visited[len]={};
p L1={-1,-1},L2={-1,-1};
int bfs();
queue<p> q;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
bool check(int x,int y){
	return (0<=x&&x<R&&0<=y&&y<C);
}
int main(){
	cin>>R>>C;
	for(int i=0;i<R;i++){
		cin>>hosu[i];
		for(int j=0;j<hosu[i].size();j++){
			if(hosu[i][j]=='.'||hosu[i][j]=='L'){
					int xy=xy2i(i,j);
					q.push({0,xy});
					visited[xy]=true;
			}
			if(hosu[i][j]=='L'){
				if(L1.first==-1)
					L1={i,j};
				else
					L2={i,j};
			}
		}
	}
	for(int i=0;i<=1500;i++){
		for(int j=0;j<=1500;j++){
			par[xy2i(i,j)]=xy2i(i,j);
		}
	}
	int day=bfs();
	cout<<day<<endl;
}
int bfs(){
	while(!q.empty()){
		p cur=i2xy(q.front().second);
		int cx=cur.first;
		int cy=cur.second;
		int cday=q.front().first;
		q.pop();
		for(int x=0;x<4;x++){
			int nx=cx+dx[x];
			int ny=cy+dy[x];
			if(check(nx,ny)){
				int cxy=xy2i(cx,cy);
				int nxy=xy2i(nx,ny);
				int dt=(hosu[nx][ny]=='X'&&!visited[nxy]?1:0);
				int nday=cday+dt;
				merge(cxy,nxy);
				if(find(xy2i(L1))==find(xy2i(L2)))
					return max(wday[nxy],wday[cxy]);
				if(!visited[nxy]){
					wday[nxy]=nday;
					visited[nxy]=true;
					q.push({nday,nxy});
				}
			}
		}
	}
}