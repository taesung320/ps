#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int par[1001]={};
bool vstd[1001]={};
vector<int> enm[1001]={};
int N,M,a,b;
char ef;
int find(int x){
	if(par[x]==x) return x;
	else return par[x]=find(par[x]);
}
void merge(int x,int y){
	int tx=find(x);
	int ty=find(y);
	if(tx==ty) return;
	else{
		par[tx]=ty;
	}
}
void enm_bfs(int i)
{
	queue<int> q;
	q.push(i);
	vstd[i]=true;
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		for(int j=0;j<enm[cur].size();j++)
		{
			int next=enm[cur][j];
			for(int k=0;k<enm[next].size();k++)
			{
				int frnd=enm[next][k];
				if(vstd[frnd]==false)
				{
					vstd[frnd]=true;
					q.push(frnd);
					merge(cur,frnd);
				}
			}
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>M;
	for(int i=1;i<=N;i++)
		par[i]=i;
	for(int i=0;i<M;i++){
		cin>>ef>>a>>b;
		if(ef=='F')
			merge(a,b);
		else{
			enm[a].push_back(b);
			enm[b].push_back(a);
		}
	}
	for(int i=1;i<=N;i++)
	{
		if(vstd[i]==false)
		enm_bfs(i);	
	}
	/////////////////////////////////////////////
	bool check[1001]={};
	int ans=0;
	for(int i=1;i<=N;i++){
		int fnd=find(i);
		if(check[fnd]==false){
			ans++;
			check[fnd]=true;
		}
	}
	cout<<ans;	
}