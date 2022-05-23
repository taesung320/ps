#include<iostream>
using namespace std;
#include<cstring>
int arr[101]={};
int cache[101][1001]={};
int N,S,M;

int DP(int idx,int vol){
	if(idx==N) return vol;
	int& ret=cache[idx][vol];
	if(ret!=-1) return ret;
	int temp1=-2;
	int temp2=-2;
	if(vol+arr[idx]<=M)
		temp1=DP(idx+1,vol+arr[idx]);
	if(vol-arr[idx]>=0)
		temp2=DP(idx+1,vol-arr[idx]);
	return ret=max(temp1,temp2);
}


int main(){
	memset(cache,-1,sizeof(cache));
	cin>>N>>S>>M;
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	int ans=DP(0,S);
	cout<<(ans!=-2?ans:-1);
}