
#include<iostream>
#include<algorithm>
#include<cstring>
#include<utility>
using namespace std;
const int INF=1e9;
int N;
int dp[17][(1<<16)]={};
int edge[17][17]={};

int DP(int com,int cur){

	int& ret=dp[cur][com];
	if(com==((1<<N)-1))
	{
		if(edge[cur][1]!=INF)
			return edge[cur][1];
		return INF;
	}
	if(ret!=-1){
		return ret;
	} 
	ret=INF;
	for(int i=1;i<=N;i++){
		if(!(com&(1<<i-1))&&edge[cur][i]!=INF){
			int temp=edge[cur][i]+DP(com+(1<<(i-1)),i);
			ret=min(ret,temp);
		}
	}
	return ret;
}
int main()
{
	memset(dp,-1,sizeof(dp));
	cin>>N;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
		{
			int x;
			cin>>x;
			edge[i][j]=(x?x:INF);
		}
			
	int ans=DP(1,1);
	cout<<ans;
}