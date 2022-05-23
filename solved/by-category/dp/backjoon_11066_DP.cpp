#include<iostream>
#include<algorithm>
using namespace std;
#include<cstring>

int cache[500][500]={};
int arr[500]={};
int sum[500]={};
int K;
int DP(int s,int e);
int sumAB(int s,int e);
void init();
int main(){
	int T;
	cin>>T;
	cout<<endl;
	while(T--){
		init();
		cin>>K;
		for(int i=0;i<K;i++){
			cin>>arr[i];
			if(i){
				sum[i]=sum[i-1]+arr[i];
			}else{
				sum[i]=arr[i];
			}
		}
		int ans=DP(0,K-1);
		cout<<ans<<"\n";
	}
}
int DP(int s,int e){
	if(s==e) return 0;
	if(s+1==e) return (arr[s]+arr[e]);
	int& ret=cache[s][e];
	if(ret!=-1) return ret;
	ret=1e9;
	for(int i=s;i<=e-1;i++){
		int pre=DP(s,i);
		int post=DP(i+1,e);
		ret=min(ret,pre+post+sumAB(s,e));
	}
	return ret;
}
void init(){
	memset(cache,-1,sizeof(cache));
	memset(arr,0,sizeof(arr));
}
int sumAB(int s,int e){
	if(s==0) return sum[e];
	return sum[e]-sum[s-1];
}



