#include<iostream>
#include<cstring>
using namespace std;
typedef long long int ll;
int N;
int fin;
ll cache[101][21]={};
int arr[101]={};
ll DP(int idx,int num){
	if(num<0||num>20) return 0;
	if(idx==N-1){
		if(num==fin) return 1;
		else return 0;
	}
	ll& ret=cache[idx][num];
	if(ret!=-1) return ret;
	return ret=DP(idx+1,num+arr[idx+1])+DP(idx+1,num-arr[idx+1]);
}
int main(){
	cin>>N;
	for(int i=1;i<N;i++){
		cin>>arr[i];
	}
	cin>>fin;
	memset(cache,-1,sizeof(cache));
	ll ans=DP(1,arr[1]);
	cout<<ans;
}