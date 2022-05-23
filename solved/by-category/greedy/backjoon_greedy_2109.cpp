#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> rec;
#define day first
#define pay second
priority_queue<int,vector<int>> pq;
rec arr[10001]={};
int main()
{
	int N;
	cin>>N;
	for(int i=1;i<=N;i++)
		cin>>arr[i].pay>>arr[i].day;
	sort(arr+1,arr+1+N);
	int last=arr[N].day,ans=0;
	for(int i=N;i>=0;)
	{
		if(arr[i].day==last)
		{
			pq.push(arr[i].pay);
			i--;
		}
		else
		{
			while(last!=arr[i].day)
			{
				if(pq.empty())
					last=arr[i].day;
				else
				{
					ans+=pq.top();
					pq.pop();
					last--;
				}
			}
		}
	}
	cout<<ans;
}