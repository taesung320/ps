#include<iostream>
#include<stack>
#include<utility>
#include<string>
using namespace std;
typedef pair<int,int> pnt;
#define r first
#define c second
bool check[10002][502]={};
bool fild[10002][502]={};
int dr[3]={-1,0,1};
int R,C,ans=0;
bool dfs(int i)
{
	stack<pnt> pq;
	pq.push({i,1});
	check[i][1]=true;
	while(!pq.empty())
	{
		pnt cur=pq.top();
		if(cur.c==C)
			return true;
		for(int j=0;j<3;j++)
		{
			pnt next={cur.r+dr[j],cur.c+1};
			if(fild[next.r][next.c]&&!check[next.r][next.c])
			{
				check[next.r][next.c]=true;
				pq.push({next.r,next.c});
				break;
			}
			if(j==2) pq.pop();
		}
	}
	return false;
}
int main()
{
	cin>>R>>C;
	string s;
	for(int i=1;i<=R;i++)
	{
		cin>>s;
		for(int j=0;j<s.size();j++)
			if(s[j]=='.')
				fild[i][j+1]=true;
		
	}
	for(int i=1;i<=R;i++)
	{
		ans+=dfs(i);
		//for(int j=1;j<=R;j++)
		//	for(int k=1;k<=C;k++)
		//		cout<<(check[j][k]?"v":"o")<<(k==C?"\n":" ");
		//cout<<endl;
	}
		
	cout<<ans;
}