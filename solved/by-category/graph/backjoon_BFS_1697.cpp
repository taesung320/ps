#include<iostream>
using namespace std;
#include<queue>
const int maxi=100001;
int dstc[maxi]={};
//이동 가능한 경우--> push , check 0,1 대신 (0,inf)..
int bfs(int s,int end)
{
	queue<int> q;
	q.push(s);
	dstc[s]=1;
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		if(cur==end)
			return (dstc[cur]-1>=0?dstc[cur]-1:0);
		for(int i=0;i<3;i++)
		{
			int next=0;
			if(i==0)
				next=cur*2;
			else if(i==1)
				next=cur-1;
			else if(i==2)
				next=cur+1;
			if(0<=next&&next<maxi&&dstc[next]==0)
			{
				dstc[next]=dstc[cur]+1;
				q.push(next);
			}
		}
	}
	return 0;
}

int main()
{
	int N,K;
	cin>>N>>K;
	int ans=bfs(N,K);
	cout<<ans;
	return 0;
}