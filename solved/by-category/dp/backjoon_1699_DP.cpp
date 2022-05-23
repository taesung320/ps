#include<iostream>
#include<algorithm>
using namespace std;

int cache[100001]={};
int square[1000]={};
const int INF=1e9;
int cnt=0;
int DP(int num)
{
	if(cache[num]!=INF)
		return cache[num];
	if(num==0)
	{
		cache[num]=0;
		return cache[num];
	}
	for(int i=1;i<=cnt;i++)
	{
		if(num>=square[i])
		cache[num]=min(cache[num],1+DP(num-square[i]));
		else
			break;
	}
	return cache[num];
	
}
int main(	)
{
	int N;
	cin>>N;
	for(int i=1;i<=N;i++)
		cache[i]=INF;
	for(int i=1;i*i<=N;i++)
	{
		square[i]=i*i;
		cnt++;
	}
	int ans=DP(N);
	cout<<ans;
}