#include<iostream>
#include<cstring>
using namespace std;

int cache[50000][4]={};
int arr[50000]={};
int N,K;
int sum[50000]={};
int DP(int idx,int cart){
	if(idx>=N) return 0;
	if(cart==0) return 0;
	int& ret=cache[idx][cart];
	if(ret!=-1)return ret;
	ret=max(DP(idx+1,cart),sum[idx]+DP(idx+K,cart-1));
	return ret;
}
int main(){
	cin>>N;
	memset(cache,-1,sizeof(cache));
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	cin>>K;
	for(int i=0;i<K;i++){
		sum[0]+=arr[i];
	}
	for(int i=1;i<N-K+1;i++){
		sum[i]=sum[i-1]-arr[i-1]+arr[i+K-1];
	}
	cout<<DP(0,3);
}