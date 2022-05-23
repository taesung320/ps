#include<iostream>
#include<algorithm>
using namespace std;
int DP[100001]={};
int arr[100001]={};
int main()
{
	int N;
	cin>>N;
	for(int i=0;i<N;i++)
	{
		cin>>arr[i];
	}
	DP[0]=arr[0];
	for(int i=1;i<N;i++)
	{
		DP[i]=arr[i]+max(0,DP[i-1]);
	}
	int ans=DP[0];
	for(int i=1;i<N;i++)
	{
		ans=max(ans,DP[i]);
	}
	cout<<ans;
}