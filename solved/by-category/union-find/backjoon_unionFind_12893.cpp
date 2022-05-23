#include<iostream>
using namespace std;

int flag[2001]={};
int par[2001]={};
int N,M,a,b;
int find(int x)
{
	if(par[x]==x) return x;
	else return par[x]=find(par[x]);
}
void flipGroup(int x)
{
	for(int i=1;i<=N;i++)
		if(find(i)==x)
			flag[i]=!flag[i];
}
bool merge(int x,int y)
{
	int tx=find(x);
	int ty=find(y);
	if(tx==ty) return flag[x]!=flag[y];
	else
	{
		if(flag[x]==flag[y]) flipGroup(tx);
		par[tx]=ty;
		return true;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>M;
	for(int i=1;i<=N;i++)
		par[i]=i;
	for(int i=0;i<M;i++){
		
		cin>>a>>b;
		if(!merge(a,b)){
			cout<<0;
			return 0;
		}
	}
	cout<<1;
}