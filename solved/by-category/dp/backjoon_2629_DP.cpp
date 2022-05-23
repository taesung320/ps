#include<iostream>
#include<cstring>
using namespace std;

int N,M;
int arr[31]={};
bool cache[31][40001]={};
int mi(int a){
	if(a<0) return a*(-1);
	return a;
}
int zz[3]={-1,0,1};
void DP(int i,int sum){
	if(i==N) return;
	for(int x=0;x<3;x++){
		int temp=mi(sum+arr[i]*zz[x]);
		if(cache[i][temp]==false){
			cache[i][temp]=true;
			DP(i+1,temp);
		}
	}
}
int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	DP(0,0);
	for(int i=0;i<N;i++){
		cache[i][arr[i]]=true;
	}
	cin>>M;
	for(int i=0;i<M;i++){
		int x;
		cin>>x;
		bool t=false;
		for(int i=0;i<N;i++){
			if(cache[i][x])
				t=true;
		}
		cout<<(t?"Y ":"N ");
	}
}