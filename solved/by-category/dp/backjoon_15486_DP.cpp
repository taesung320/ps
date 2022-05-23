#include<iostream>
#include<cstring>
using namespace std;
const int M=1500001;
int cache[M]={};
int t[M]={};
int p[M]={};
int N;
int DP(int d){
	if(d>N) return 0;
	if(cache[d]!=-1) return cache[d];
	if(d-1+t[d]>N) p[d]=0;
	return cache[d]=max(p[d]+DP(d+t[d]),DP(d+1));
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	memset(cache,-1,sizeof(cache));
	cin>>N;
	for(int i=1;i<=N;i++)
		cin>>t[i]>>p[i];
	cout<<DP(1);
}