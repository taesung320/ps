#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

typedef pair<int,int> p;
typedef pair<p,int> node;
vector<p> vrs;
const int INF=1e9;
const int virus=2;
const int wall=1;
int N,M,cleanZone=0;
bool last=false;
int arr[50][50]={};
bool check(int x,int y){
	return (0<=x&&x<N)&&(0<=y&&y<N);
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int bfs(vector<int> vv){
	queue<node> q;
	bool visited[50][50]={};
	for(int i=0;i<vv.size();i++){
		int tx=vrs[vv[i]].first;
		int ty=vrs[vv[i]].second;
		visited[tx][ty]=true;
		q.push({{tx,ty},0});
	}
	int ans=0;
	int tempClean=cleanZone;
	while(!q.empty()){
		p cp=q.front().first;
		int ct=q.front().second;
		int cx=cp.first;
		int cy=cp.second;
		q.pop();
		bool moved=false;
		for(int k=0;k<4;k++){
			int nx=cx+dx[k];
			int ny=cy+dy[k];
			int nt=ct+1;
			if(check(nx,ny)&&arr[nx][ny]!=wall&&!visited[nx][ny]){
				visited[nx][ny]=true;
				moved=true;
				q.push({{nx,ny},nt});
				tempClean--;
				if(arr[nx][ny]==0)
				ans=max(ans,nt);
			}
		}
	}
	return (!tempClean?(ans-(last?1:0)):INF);
}
int solve(){
	int ans=INF;
	for(int i=((1<<M)-1);i<(1<<vrs.size());i++){
		vector<int> temp;
		for(int j=0;j<10;j++){
			if(i&(1<<j)){
				temp.push_back(j);
			}
			if(temp.size()>M)
				break;
		}
		if(temp.size()==M)
			ans=min(ans,bfs(temp));
	}
	return ans;
}


int main(){
	cin>>N>>M;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>arr[i][j];
			if(arr[i][j]==virus){
				vrs.push_back({i,j});
			}
			if(arr[i][j]==0) cleanZone++;
		}
	}
	cleanZone+=(vrs.size()-M);
	int ans=solve();
	cout<<(ans!=INF?ans:-1);
}