#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll cache[101]={};
ll DP(int N){
	if(N<1) return 0;
	if(N==1) return 1;
	ll& ret=cache[N];
	if(ret!=-1) return ret;
	ret=DP(N-1)+1;
	for(int k=3;k<=N-1;k++){
		ret=max(ret,(k-1)*DP(N-k));
	}
	return ret;
}
int main(){
	int N;
	cin>>N;
	memset(cache,-1,sizeof(cache));
	cout<<DP(N);
}