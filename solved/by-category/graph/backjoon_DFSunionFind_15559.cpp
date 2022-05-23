#include<iostream>
#include<string>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int N,M;
int arr[1002][1002]={};
bool visited[1002][1002]={};
int dx[]={0,1,-1,0,0};
int dy[]={0,0,0,1,-1};//SNEW]
int par[11111111]={};
bool check[11111111]={};
int ij2x(int i,int j){
	return (10000*i+j);
}
//________
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
	else par[ty]=tx;
}

int c2i(char c){
	if(c=='S') return 1;
	else if(c=='N') return 2;
	else if(c=='E') return 3;
	else if(c=='W') return 4;
	return 0;
}
void dfs(int i,int j);
int main(){
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		string s;
		cin>>s;
		for(int j=0;j<s.size();j++){
			arr[i][j+1]=c2i(s[j]);
			par[ij2x(i,j+1)]=ij2x(i,j+1);
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(!visited[i][j]){
				dfs(i,j);
			}
		}	
	}

	int ans=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(!check[find(ij2x(i,j))]){
				check[find(ij2x(i,j))]=true;
				ans++;
			}
		}
	}
	cout<<ans;
}
void dfs(int i,int j){
	visited[i][j]=true;
	int nexti=i+dx[arr[i][j]];
	int nextj=j+dy[arr[i][j]];
	merge(ij2x(i,j),ij2x(nextj,nextj));
	if(arr[nexti][nextj]&&!visited[nexti][nextj]){
		dfs(nexti,nextj);
	}

}