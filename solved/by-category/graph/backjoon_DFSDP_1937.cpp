#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int arr[502][502]={};
int cache[502][502]={};
int K=0,N=0;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int dfs(int x,int y){
	int& ret=cache[x][y];
	if(ret) return ret;
	ret=1;
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
        int ny=y+dy[i];
		if(arr[x][y]<arr[nx][ny]){
			ret=max(ret,1+dfs(nx,ny));
		}
	}
	K=max(K,ret);
	return ret;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			cin>>arr[i][j];
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
				dfs(i,j);
		}
	}
	cout<<K+1;
}
