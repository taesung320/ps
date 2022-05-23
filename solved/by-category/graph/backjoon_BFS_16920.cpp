#include<iostream>
#include<queue>
#include<utility>
#include<cstring>
#include<string>
using namespace std;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int s[10]={};
int ans[10]={};
int board[1002][1002]={};
typedef pair<int,int> point;
queue<point> userQ[10]={};
void BFS(int n)
{
	int cnt=n;
	int turn=0;
	
	while(true)
	{
		int remain=0;
		for(int i=1;i<=n;i++)
		{
			while(!userQ[i].empty())
			{
				point fp=userQ[i].front();
				int curN=board[fp.first][fp.second];
				if((curN-1)%s[i]==0&&(curN-1)/s[i]>turn)
					 break;
				userQ[i].pop();
				for(int j=0;j<4;j++)
				{
					int next_x=fp.first+dx[j];
					int next_y=fp.second+dy[j];
					if(board[next_x][next_y]==0)
					{
						board[next_x][next_y]=curN+1;
						userQ[i].push(point(next_x,next_y));
						ans[i]++;
					}
				}
			}
			if(!userQ[i].empty())
				remain++;
		}
		if(!remain)
			break;
		turn++;
	}
}
int main()
{
	memset(board, -1, sizeof(board));
	int N,M,P;
	cin>>N>>M>>P;
	for(int i=1;i<=P;i++)
	{
		cin>>s[i];
	}
	string s;
	for(int i=1;i<=N;i++)
	{
		cin>>s;
		for(int j=0;j<M;j++)
		{
			if(s[j]=='.')
			{
				board[i][j+1]=0;
			}
			else if(s[j]=='#')
			{
				board[i][j+1]=-1;
			}
			else 
			{
				board[i][j+1]=1;
				userQ[int(s[j]-'0')].push(point(i,j+1));
				ans[int(s[j]-'0')]++;
			}
		}
	}
	for(int i=0;i<N+2;i++)
		for(int j=0;j<M+2;j++)
			cout<<board[i][j]<<(j==M+1?"\n":" ");
	BFS(P);
	for(int i=1;i<=P;i++)
		cout<<ans[i]<<" ";
	
}