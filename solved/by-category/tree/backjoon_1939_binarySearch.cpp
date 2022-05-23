#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
int s,m,e;
int s1,s2;
typedef pair<int,int> ed;
vector<ed> plant[10001];
bool nextState(int d)
{
	if(d==1)
	{
		s=m+1;
		m=(s+e)/2;
	}
	else if(d==-1)
	{
		e=m-1;
		m=(s+e)/2;
	}
	if(s<=e)
		return true;
	else
		return false;
		
}
int dfs(int wei)
{
	bool check[10001]={};
	queue<int> v;
	v.push(s1);
	check[s1]=true;
	while(!v.empty())
	{
		int cur=v.front();
		v.pop();
		if(cur==s2)
			return 1;
		vector<ed> temp=plant[cur];
		for(int i=0;i<temp.size();i++)
		{
			if(check[temp[i].first]==false&&temp[i].second>=wei)
			{
				check[temp[i].first]=true;
				v.push(temp[i].first);
			}
		}
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,M;
	cin>>N>>M;
	int v1,v2,w=0,wMin=1e9,wMax=0;
	for(int i=0;i<M;i++)
	{
		cin>>v1>>v2>>w;
		plant[v1].push_back(ed(v2,w));
		plant[v2].push_back(ed(v1,w));
		wMax=max(wMax,w);
		wMin=min(wMin,w);
	}
	cin>>s1>>s2;
	s=wMin;
	m=(wMin+wMax)/2;
	e=wMax;
	int ans=-1;
	while(true)
	{
		int yn=dfs(m);
		if(yn==1)
			ans=max(ans,m);
		if(!nextState(yn))
			break;
	}
	cout<<ans;
}