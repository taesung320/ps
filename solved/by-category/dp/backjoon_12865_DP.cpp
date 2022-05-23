#include<iostream>
#include<cstring>
using namespace std;
int N,K;
int w[100]={};
int v[100]={};
int cache[100001][100]={};
int DP(int i,int weight){
	if(weight<0) return 0;
	if(i>=N) return 0;
	int& ret=cache[weight][i];
	if(ret!=-1)return ret;
	return ret=max((w[i]<=weight?v[i]:0)+DP(i+1,weight-w[i]),DP(i+1,weight));
}

int main(){
	memset(cache,-1,sizeof(cache));
	cin>>N>>K;
	for(int i=0;i<N;i++){
		cin>>w[i]>>v[i];
	}
	cout<<DP(0,K);
}