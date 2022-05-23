#include<iostream>
using namespace std;
int par[300001]={};
bool isin[300001]={};
int find(int x)
{
	if(x==par[x])
		return x;
	else
		return par[x]=find(par[x]);// dp 같은느낌 경로 압축
}
void merge(int x,int y)
{
	int tx=find(x);
	int ty=find(y);
	if(tx==ty) return ;
	else par[tx]=ty;
}
int main()
{
	int N,L;
	cin>>N>>L;
	for(int i=1;i<=L;i++)
		par[i]=i;
	for(int i=0;i<N;i++)
	{
		int a,b;
		cin>>a>>b;
		if(par[a]==a){
			isin[a]=true;
			merge(a,b);
		}
		else if(par[b]==b){
			isin[b]=true;
			merge(b,a);
		}
		else if(isin[par[a]]==false)
		{
			isin[par[a]]=true;
			merge(a,b);
		}
		else if(isin[par[b]]==false)
		{
			isin[par[b]]=true;
			merge(b,a);
		}
		else
		{
			cout<<"SMECE\n";
			continue;
		}
		cout<< "LADICA\n";
		
	}
}