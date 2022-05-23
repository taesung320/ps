#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int cache1[1001][4][3]={};
int cache2[1001][3]={};
const int modn=1000000007;
int DP1(int n,int x,int m){//n 앞으로 채울거 , x 여태 이어진거, m 이어진 선읹당개수
	if(n==0) return 1;
	int& ret=cache1[n][x][m];
	if(ret!=-1) return ret;	
	ret=0;
	if(x==0){//0
		ret=((DP1(n-1,0,0)+DP1(n-1,1,1))%modn)+DP1(n-1,2,1);
	}else if(x==1||x==2){//1,2
		ret=((x==1?DP1(n-1,2,2):0)+(m<2?DP1(n-1,3,2):0))%modn+DP1(n-1,0,0);
	}else if(x==3){//2
		ret=DP1(n-1,0,0);	
	}
	ret%=modn;
	return ret;
}
int DP2(int n,int x){//n 앞으로 채울거 , x 여태 이어진거 
	if(n==0) return 1;
	int& ret=cache2[n][x];
	if(ret!=-1) return ret;	
	ret=0;
	if(x==0){
		ret=DP2(n-1,0)+DP2(n-1,1);
	}else if(x==1){
		ret=DP2(n-1,2)+DP2(n-1,0);
	}else if(x==2){
		ret=DP2(n-1,0);	
	}
	ret%=modn;
	return ret;
}
int main(){
	memset(cache1,-1,sizeof(cache1));
	memset(cache2,-1,sizeof(cache2));
	int N;
	cin>>N;
	cout<<(DP1(N-1,0,0)-DP2(N-1,0)+modn)%modn;
}
