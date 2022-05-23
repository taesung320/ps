#include<iostream>
#include<cstring>
using namespace std;
int cache[61][61][61]={};//체력 조합이 [],[],[] 일때 죽이는 최소횟수
int arr[3]={};
int N;
int m1[]={9,9,3,3,1,1};
int m2[]={3,1,9,1,3,9};
int m3[]={1,3,1,9,9,3};
int p(int x){
	return (x<0?0:x);
}
int DP(int s1,int s2,int s3){
	if(!(s1||s2||s3)) return 0;
	int& ret=cache[s1][s2][s3];
	if(ret!=-1) return ret;
	ret=1e9;
	for(int x=0;x<6;x++){
		ret=min(ret,1+DP(p(s1-m1[x]),p(s2-m2[x]),p(s3-m3[x])));
	}
	return ret;
}
int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	memset(cache,-1,sizeof(cache));
	int ans=DP(arr[0],arr[1],arr[2]);
	cout<<ans;
}