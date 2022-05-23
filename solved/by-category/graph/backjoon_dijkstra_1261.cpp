#include<iostream>
#include<queue>
#include<string>
#include<utility>
using namespace std;

typedef pair<int,int> point;
typedef pair<int,point> info;

const int INF=1e9;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool board[102][102]={};
int dist[102][102]={};
priority_queue<info,vector<info>,greater<info>> pq;

int dijk(int N,int M)
{

	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			dist[i][j]=INF;
	dist[1][1]=0;
	pq.push(info(0,point(1,1)));
	while(!pq.empty())
	{
		point cur_p=pq.top().second;
		int cost=pq.top().first;
		pq.pop();
		if(cur_p.first==M&&cur_p.second==N)
			return dist[M][N];
		if(cost>dist[cur_p.first][cur_p.second])
			continue;
		for(int i=0;i<4;i++)
		{
			int next_x=cur_p.first+dx[i];
			int next_y=cur_p.second+dy[i];
			int next_cost=cost;
			if(1<=next_x&&next_x<=M&&1<=next_y&&next_y<=N)
			{
				if(!board[next_x][next_y])
					next_cost++;
				if(dist[next_x][next_y]>next_cost)
				{
					dist[next_x][next_y]=next_cost;
					pq.push(info(next_cost,point(next_x,next_y)));
				}
			}
		}
	}
	return dist[M][N];
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,M;
	cin>>N>>M;
	for(int i=1;i<=M;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<s.size();j++)
		{
			if(s[j]=='0')
				board[i][j+1]=true;
		}
	}
	int ans=dijk(N,M);
	cout<<ans;
}