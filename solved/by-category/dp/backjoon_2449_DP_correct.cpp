#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int INF=1e9;
int N,K;
int rgt[201]={};
int cache[201][201]={};
bool is_mono(int start,int end){
	for(int i=start;i<end;i++)
		if(rgt[i]!=rgt[i+1]) return false;
	return true;
}
int DP(int start,int end){
	int& ret=cache[start][end];
	if(ret!=-1) return ret;
	//if(is_mono(start,end)) return ret=0;
	if(end-start<=1&&rgt[end]==rgt[start]) return ret=0;
	ret=INF;
	for(int i=start;i<end;i++)
	{
		ret=min(ret,DP(start,i)+DP(i+1,end)+(rgt[start]==rgt[i+1]?0:1));
	}
	return ret;
}
int main()
{
	memset(cache,-1,sizeof(cache));
	cin>>N>>K;
	for(int i=1;i<=N;i++)
		cin>>rgt[i];
	int ans=DP(1,N);
	cout<<ans;
}