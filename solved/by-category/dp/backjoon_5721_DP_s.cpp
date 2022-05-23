#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
vector<int> temp;//행
vector<int> result;//행별 최대값
vector<int> tempCache(100000);
//dp랑 dp2랑 차이는 없드라.
int dp(int n)//배열 n번째 index까지 최대값
{
	if(n<0)
		return 0;
	if(n==0)
		return tempCache[n]=temp[n];
	if(tempCache[n]!=-1)
		return tempCache[n];
	tempCache[n]=temp[n]+max(dp(n-2),dp(n-3));
	tempCache[n]=max(tempCache[n],dp(n-1));
	return tempCache[n];
}
int dp2(int n)
{
	if(temp.size()>=1)
	tempCache[0]=temp[0];
	if(temp.size()>=2)
	tempCache[1]=max(temp[0],temp[1]);
	if(temp.size()>=3)
	tempCache[2]=max(temp[2]+temp[0],temp[1]);
	if(temp.size()>=4)
	{
	for(int i=3;i<temp.size();i++)
	{
		tempCache[i]=max(tempCache[i-1],temp[i]+max(tempCache[i-2],tempCache[i-3]));
	}
	}
	return tempCache[n];
}
int getMax(vector<int> v)//배열에서 합최대(문제조건맞게)
{
	for(int i=0;i<v.size();i++)
		tempCache[i]=-1;
	return dp2(v.size()-1);
}
void clearV()
{
	vector<int> empty;
	tempCache=empty;
	temp=empty;
	result=empty;
}


int main()
{while(true)
{
	
vector<int> arr[100000];
	int N,M;
	cin>>N>>M;
	if(N*M==0)
		return 0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			int a;
			cin>>a;
			arr[i].push_back(a);
		}
	for(int i=0;i<N;i++)
	{
		temp=arr[i];//i 행
		result.push_back(getMax(temp));//i행의 합의 최대를 구해서 넣엊ㅁ
	}
	temp=result;
	int ans=getMax(temp);//행의합의 최대들의 합의최대를 구ㅎ마
	cout<<ans<<"\n";
	clearV();//벡터들 다시 비워줌
			
}
}