#include<iostream>
#include<cstring>
using namespace std;

int cache[2000][2000]={};//[a][b] : a~b가 펠린드롬인가?
int arr[2000]={};
int N;
int DP(int s,int e){
	int& ret=cache[s][e];
	if(ret!=-1) return ret;
	if(s==e) return ret=true;
	if(arr[s]!=arr[e]) return ret=false;
	if(s+1==e)return ret=(arr[s]==arr[e]);
	return ret=DP(s+1,e-1);
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	memset(cache,-1,sizeof(cache));
	cin>>N;
	for(int i=0;i<N;i++)
		cin>>arr[i];
	for(int i=0;i<N;i++){
		for(int j=i;j<N;j++){
			if(cache[i][j]==-1)
			DP(i,j);
		}
	}
	int M;
	cin>>M;
	for(int i=0;i<M;i++){
		int a,b;
		cin>>a>>b;
		cout<<cache[a-1][b-1]<<"\n";
	}
}