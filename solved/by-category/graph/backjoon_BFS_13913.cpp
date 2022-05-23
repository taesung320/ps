#include<iostream>
using namespace std;
#include<queue>
#include<stack>
#include<utility>
typedef pair<int,int> node;
node info[100001];
node bfs(int N,int K)
{
	queue<int> q;
	q.push(N);
	info[N]=node(N,0);
	while(!q.empty())
	{
		int f=q.front();
		if(f==K)
			return info[K];
		q.pop();
		int next=f;
		for(int i=0;i<3;i++)
		{
			if(i==0)
				next=f+1;
			else if(i==1)
				next=f-1;
			else
				next=2*f;
			if(0<=next&&next<=100000&&info[next].second==0)
			{
				info[next].first=f;
				info[next].second=info[f].second+1;
				q.push(next);
			}
				
		}
	}
	return info[K];
	
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,K;
	cin>>N>>K;
	node ans=bfs(N,K);
	int cur=N;
	cout<<ans.second<<'\n';
	stack<int> ansQ;
	ansQ.push(K);
	while(ansQ.size()!=ans.second+1)
	{
		ansQ.push(info[ansQ.top()].first);
	}
	while(!ansQ.empty())
	{
		cout<<ansQ.top()<<" ";
		ansQ.pop();
	}
}