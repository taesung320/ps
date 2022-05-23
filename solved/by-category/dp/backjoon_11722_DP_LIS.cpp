#include<iostream>
#include<algorithm>
using namespace std;
int arr[1000]={};
int cache[1000]={};
int N;
int Lis(int num)
{
	if(cache[num]!=0)
		return cache[num];
	cache[num]=1;
	for(int i=num;i<N;i++)
	{
		if(arr[num]<arr[i])
		cache[num]=max(cache[num],Lis(i)+1);
	}
	return cache[num];
}
int main()
{
	
	cin>>N;
	for(int i=0;i<N;i++)
	{
		int temp;
		cin>>temp;
		arr[i]=temp*(-1);
	}
		
	int ans=0;
	for(int i=0;i<N;i++)
	{
		ans=max(Lis(i),ans);
	}
	cout<<ans;
}