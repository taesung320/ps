#include<iostream>
#include<cstring>
using namespace std;
int N,M;
int arr[502][502]={};
int cache[502][502]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int dfs(int x,int y){
	if(x==N&&y==M) return 1;
	int& ret=cache[x][y];
	if(ret!=-1) return ret;
	ret=0;
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(!arr[nx][ny]) continue;
		if(arr[nx][ny]&&arr[x][y]>arr[nx][ny])
			ret+=dfs(nx,ny);
	}
	return ret;
}
int main(){
	memset(cache,-1,sizeof(cache));
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			cin>>arr[i][j];
		}
	}
	int ans=dfs(1,1);
	cout<<ans;
}