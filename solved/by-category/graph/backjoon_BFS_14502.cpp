#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;
typedef pair<int,int> p;
typedef pair<int,int> node;
vector<p> wll;
const int virus=2;
const int wall=1;
int N,M,cleanZone=0;
bool last=false;
int arr[50][50]={};
bool check(int x,int y){
	return (0<=x&&x<N)&&(0<=y&&y<M);
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
queue<node> Q;
vector<vector<bool>> vstd;
int bfs(){
	queue<node> q=Q;
	vector<vector<bool>> visited=vstd;
	int tempClean=cleanZone;
	while(!q.empty()){
		p cp=q.front();
		int cx=cp.first;
		int cy=cp.second;
		q.pop();
		for(int k=0;k<4;k++){
			int nx=cx+dx[k];
			int ny=cy+dy[k];
			if(check(nx,ny)&&arr[nx][ny]!=wall&&!visited[nx][ny]){
				visited[nx][ny]=true;
				q.push({nx,ny});
				tempClean--;
			}
		}
	}
	return tempClean;
}
int solve(){
	int ans=0;
	int sz=wll.size();
	for(int i=0;i<sz;i++)
		for(int j=i+1;j<sz;j++)
			for(int k=j+1;k<sz;k++){
				int ix=wll[i].first,iy=wll[i].second;
				int jx=wll[j].first,jy=wll[j].second;
				int kx=wll[k].first,ky=wll[k].second;
				arr[ix][iy]=arr[jx][jy]=arr[kx][ky]=1;
				ans=max(ans,bfs());
				arr[ix][iy]=arr[jx][jy]=arr[kx][ky]=0;
			}
	return ans;
}
int main(){
	cin>>N>>M;
	for(int i=0;i<N;i++){
		vector<bool> el(M);
		vstd.push_back(el);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
			if(arr[i][j]==0){
				wll.push_back({i,j});
				cleanZone++;
			}else if(arr[i][j]==virus){
				Q.push({i,j});
				vstd[i][j]=true;
			} 
		}
	}
	int ans=solve();
	cout<<ans-3;
}