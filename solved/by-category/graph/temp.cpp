#include<iostream>
using namespace std;
#include<queue>
#include<utility>
queue<char> info[100001];
const int def=-1;
const int add=0;
const int sub=1;
const int mul=2;
const char cal[3]={'+','-','*'};
queue<char> empty;
queue<char> bfs(int N,int K)
{
	queue<int> q;
	q.push(N);
	info[N].push('A');
    empty.push('A');
	while(!q.empty())
	{
		int f=q.front();
		if(f==K)
			return info[K];
		queue<char> temp=info[f];
		info[f]=empty;
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
			if(0<=next&&next<=100000&&info[next].empty())
			{
				info[next]=temp;
				info[next].push(cal[i]);
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
	queue<char> ans=bfs(N,K);
	int cur=N;
	cout<<ans.size()-1<<'\n'<<cur<<" ";
    ans.pop();
	while(!ans.empty())
	{
		char temp=ans.front();
		ans.pop();
		if(temp==cal[add])
		{
			cur=cur+1;
		}
		else if(temp==cal[sub])
		{
			cur=cur-1;
		}
		else if(temp==cal[mul])
		{
			cur=cur*2;
		}
		cout<<cur<<" ";
	}
}