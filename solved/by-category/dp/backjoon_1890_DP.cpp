#include<iostream>
#include<cstring>
using namespace std;
typedef long long int ll;
ll cache[101][101]={};
ll arr[101][101]={};
bool visited[101][101]={};
ll N;
ll DP(ll i,ll j){
	if(!(0<=i&&i<N&&0<=j&&j<N))
		return 0;
	if(i==N-1&&j==N-1) return 1;
	if(arr[i][j]==0) return 0;
	ll& ret=cache[i][j];
	if(ret!=-1) return ret;
	ret=0;
	return ret=(DP(i+arr[i][j],j)+DP(i,j+arr[i][j]));
}

ll main(){
	memset(cache,-1,sizeof(cache));
	cin>>N;
	for(ll i=0;i<N;i++){
		for(ll j=0;j<N;j++){
			cin>>arr[i][j];
		}
	}
	ll ans=DP(0,0);
	cout<<ans;
}