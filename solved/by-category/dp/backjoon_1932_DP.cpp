#include<iostream>
#include<cstring>
using namespace std;

int arr[510][510]={};
int cache[510][510]={};
int N;
int DP(int i,int j){
	if(i==N-1) return arr[i][j];
	int& ret=cache[i][j];
	if(ret!=-1) return ret;
	return ret=arr[i][j]+max(DP(i+1,j),DP(i+1,j+1));
}

int main(){
	memset(cache,-1,sizeof(cache));
	cin>>N;
	for(int i=0;i<N;i++){
		for(int j=0;j<=i;j++){
			cin>>arr[i][j];
		}
	}
	int ans=DP(0,0);
	cout<<ans;
}