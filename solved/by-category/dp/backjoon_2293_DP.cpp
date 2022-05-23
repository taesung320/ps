#include<iostream>
using namespace std;
int num[10001]={1};
int cn[100]={};
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>cn[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(j-cn[i]>=0)
			{
				num[j]+=num[j-cn[i]];
			}
		}
	}
	cout<<num[k];
}
///////////////////////엄청난 복병이다