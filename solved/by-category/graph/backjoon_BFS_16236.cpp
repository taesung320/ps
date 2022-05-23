#include<iostream>
#include<queue>
#include<utility>
using namespace std;
//의심이 들었으면 끝까지 물어지기
typedef pair<int,int> p;
typedef pair<p,p> pp;
typedef pair<pp,int> node;
int N;
int dx[]={-1,0,0,1};
int dy[]={0,-1,1,0};
int arr[20][20]={};
bool visited[20][20][10][100]={};//위치 , 크기
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<N);
}
queue<node> q;
int bfs(){
	int ret=0;
	priority_queue<node,vector<node>,greater<node>> pq;
	priority_queue<node,vector<node>,greater<node>> emp;
	int curPQt=0;
	while(!q.empty()){
		p xy=q.front().first.first;
		p info=q.front().first.second;
		int cx=xy.first;
		int cy=xy.second;
		int cs=info.first;
		int ce=info.second;
		int ct=q.front().second;
		q.pop();
		for(int k=0;k<4;k++){
			int nx=cx+dx[k];
			int ny=cy+dy[k];
			int ns=cs;
			int ne=ce;
			if(!check(nx,ny)) continue;
			if(arr[nx][ny]==0||arr[nx][ny]==cs){
				if(!visited[nx][ny][cs][ce])
				{
					q.push({{{nx,ny},{cs,ce}},ct+1});
					visited[nx][ny][cs][ce]=true;
				}
			}else if(arr[nx][ny]<cs){
				if(pq.empty())
					curPQt=ct+1;
				if(curPQt==ct+1){
					if(ce+1==cs&&ns<7){
						ns++;
						ne=0;
					}else{
						ne++;
					}
					pq.push({{{nx,ny},{ns,ne}},ct+1});
				}
			}
		}
		//더이상 전진불가, pq에는 최단 거리의 먹이들만 존재
		if(q.empty()&&!pq.empty()){
			p xy=pq.top().first.first;
			p info=pq.top().first.second;
			int cx=xy.first;
			int cy=xy.second;
			int cs=info.first;
			int ce=info.second;
			int ct=pq.top().second;
			//cout<<cx+1<<" , "<<cy+1<<" :: "<<cs<<" / "<<ce<<" ~~ "<<ct<<endl;
			visited[cx][cy][cs][ce]=true;
			ret=ct;
			q.push(pq.top());
			arr[cx][cy]=0;
			pq=emp;
		}
	}
	return ret;
}
int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>arr[i][j];
			if(arr[i][j]==9){
				q.push({{{i,j},{2,0}},0});
				visited[i][j][2][0]=true;
				arr[i][j]=0;
			}
		}
	}
	int ans=bfs();
	cout<<ans;
}