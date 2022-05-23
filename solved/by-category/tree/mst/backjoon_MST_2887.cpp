#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define X 0
#define Y 1
#define Z 2
typedef pair<int,int> p;
typedef pair<int,pair<int,int>> pp;
vector<p> pnt[3]={};
int par[100000]={};
int find(int x)
{
	if(par[x]==x) return x;
	else return par[x]=find(par[x]);
}
void merge(int x,int y)
{
	int tx=find(x);
	int ty=find(y);
	if(tx==ty) return ;
	else{
		par[tx]=ty;
	}
}
int main()
{
	int N,x,y,z;
	int inpt[3];
	cin>>N;
	for(int i=0;i<N;i++)
	{
		cin>>inpt[X]>>inpt[Y]>>inpt[Z];
		for(int j=0;j<3;j++)
			pnt[j].push_back({inpt[j],i});
	}
	priority_queue<pp,vector<pp>,greater<pp>> pq;
	for(int i=0;i<3;i++)
		sort(pnt[i].begin(),pnt[i].end());
	for(int i=0;i<3;i++)
	{
		for(int j=1;j<N;j++)
		{
			p pnt1=pnt[i][j-1],pnt2=pnt[i][j];
			pq.push({abs(pnt1.first-pnt2.first),{pnt1.second,pnt2.second}});
		}
	}
	long long int ans=0;
	int cnt=0;
	for(int i=0;i<N;i++)
		par[i]=i;
	while(!pq.empty()&&cnt<N-1)
	{
		pp temp=pq.top();
		pq.pop();
		int len=temp.first;
		p tp=temp.second;
		if(find(tp.first)!=find(tp.second))
		{
			merge(tp.first,tp.second);
			ans+=len;
			cnt++;
		}
	}
	cout<<ans;
}









