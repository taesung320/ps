#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//그냥 완탐
int dArr[20001]={};
class entry
{
	public:
	int hide;
	int dstc;
	int cnt;
	entry(int h=0,int d=0,int c=0)
	{
		this->hide=h;
		this->dstc=d;
		this->cnt=c;
	}
};
entry bfs(vector<vector<int>> vec)
{
	queue<int> q;
	q.push(1);
	dArr[1]=1;
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		for(int i=0;i<vec[cur].size();i++)
		{
			int temp=vec[cur][i];
			if(dArr[temp]==0)
			{
				dArr[temp]=dArr[cur]+1;
				q.push(temp);
			}
		}
	}
	entry rslt;
	for(int i=1;i<vec.size();i++)
	{
		if(rslt.dstc<dArr[i])
		{
			rslt.dstc=dArr[i];
		}
	}
 
	for(int i=1;i<vec.size();i++)
	{
		if(rslt.dstc==dArr[i])
		{
			if(rslt.hide==0)
				rslt.hide=i;
			rslt.cnt++;
		}
	}
	rslt.dstc--;
	return rslt;
}
int main()
{
	int N,M;
	cin>>N>>M;
	vector<vector<int>> v(N+1);
	for(int i=0;i<M;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	entry ans=bfs(v);
	cout<<ans.hide<<" "<<ans.dstc<<" "<<ans.cnt<<"\n";
}