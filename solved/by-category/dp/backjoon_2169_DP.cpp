#include<iostream>
#include<algorithm>
using namespace std;
//처리하는 값의 범위가 음수까지 있었음을 간과했음.
int arr[1001][1001]={};
int cache[1001][1001][3]={};
int N,M;
int dx[]={1,0,0};
int dy[]={0,1,-1};
bool check(int i,int j){
	return (1<=i&&i<=N&&1<=j&&j<=M);
}
int DP(int i,int j,int dirc){
	if(i==N&&j==M) return arr[i][j];
	int& ret=cache[i][j][dirc];
	if(ret!=-1e9) return ret;
	
	for(int x=0;x<3;x++){
		if((x==1&&dirc==2)||(x==2&&dirc==1)) continue;
		int nexti=i+dx[x];
		int nextj=j+dy[x];
		if(check(nexti,nextj)){
			int temp=DP(nexti,nextj,x);
			ret=max(ret,arr[i][j]+temp);
		}
	}
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			cin>>arr[i][j];
			for(int k=0;k<3;k++)
			cache[i][j][k]=-1e9;
		}
	}
	int ans=max(DP(1,1,1),DP(1,1,0));
	cout<<ans;
}