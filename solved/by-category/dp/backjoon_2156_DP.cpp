#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int wine[10000]={};
int cache[10000][3]={};
int dpWine(int i,int j)
{
	if(i==0)
	{
		cache[i][0]=0;
		cache[i][1]=cache[i][2]=wine[0];
		return cache[i][j];
	}
	if(cache[i][j]!=-1)
		return cache[i][j];
	if(j==0)
	{
		cache[i][j]=max(dpWine(i-1,0),max(dpWine(i-1,1),dpWine(i-1,2)));
		//두번 연속 먹지않는 경우도 발생할수있다.. 예외 발견하기..!
	}
	else if(j==1)
	{
		cache[i][j]=dpWine(i-1,0)+wine[i];
	}
	else if(j==2)
	{
		cache[i][j]=dpWine(i-1,1)+wine[i];
	}
	return cache[i][j];
}
int main()
{
	memset(cache, -1, sizeof(cache));
	int N;
	cin>>N;
	for(int i=0;i<N;i++)
		cin>>wine[i];
	int ans=max(dpWine(N-1,0),max(dpWine(N-1,1),dpWine(N-1,2)));
	cout<<ans;
}