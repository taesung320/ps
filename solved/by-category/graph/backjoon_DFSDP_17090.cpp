#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int char2int(char x){
	return (x=='U'?0:(x=='R'?1:(x=='D'?2:3)));
}
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int cache[502][502];
int arr[502][502]={};
int N,M;
int dfs(int x,int y){
	if(x==N+1||y==M+1||x==0||y==0) return 1;
	int& ret=cache[x][y];
	if(ret!=-1) return ret;
	ret=0;
	int nx=x+dx[arr[x][y]];
	int ny=y+dy[arr[x][y]];
	ret+=dfs(nx,ny);
	return ret;
}
int main(){
	cin>>N>>M;
	memset(cache,-1,sizeof(cache));
	for(int i=1;i<=N;i++){
		string s;
		cin>>s;
		for(int j=1;j<=M;j++){
			arr[i][j]=char2int(s[j-1]);
		}
	}
	int ans=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(dfs(i,j)) ans++;
		}
	}
	cout<<ans;
}