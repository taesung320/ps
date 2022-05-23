#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int room[22][22]={};
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};
int dstc[11][11]={};
const int block=0;
const int space=1;
const int robot=2;
const int dirt=3;
typedef pair<int,int> point;
void bfs(const point p,int num);
vector<point> node;
//이게 약간 정점정보 주어지면 각 정점간의 거리를 bfs로 돌려서 구해서
//이걸 그래프로 만드는것--> 이건 얼마나 걸리는지 모르겠다...
//방문순서 10!이면 10*9*8*7*(6!=720)<=720*10000
void initialize()//맨 처음 while 돌아갈때마다 초기화 시켜줘야함
{
	for(int i=0;i<22;i++)
		for(int j=0;j<22;j++)
			room[i][j]=0;
	for(int i=0;i<11;i++)
		for(int j=0;j<11;j++)
			dstc[i][j]=0;
	node=vector<point>();
}
int main()
{
while(true){
	//초기화 
	initialize();
	//node 0번을 로봇을 ㄷ넣는다
	node.push_back(point(0,0));
	int w,h;
	cin>>w>>h;
	if(w*h==0)
		return 0;
	string s;
	for(int i=1;i<=h;i++)
	{
		cin>>s;
		for(int j=1;j<=w;j++)
		{
			
			if(s[j-1]=='.')
			{
				room[i][j]=space;
			}
			else if(s[j-1]=='x')
			{
				room[i][j]=block;
			}
			else if(s[j-1]=='*')
			{
				room[i][j]=dirt;
				node.push_back(point(i,j));
			}
			else if(s[j-1]=='o')
			{
				room[i][j]=robot;
				node[0]=point(i,j);
			}
		}
	}
	//인풋끝///////////////////////////////////////////////////////////////
	
	for(int i=0;i<node.size();i++)
	{
		bfs(node[i],i);//주어진 정보내에서 bfs 한번씩 돌린다.. 정점간 거리 정보 등록
	}
	/*등록이 잘됐나 확인하는 코드
	for(int i=0;i<node.size();i++)
		for(int j=0;j<node.size();j++)
			cout<<dstc[i][j]<<(j==node.size()-1?"\n":" ");
	
*/
	
	int minSize=1e9;
	vector<int> tempV;
	for(int i=0;i<node.size();i++)
	{
		tempV.push_back(i);	
	}
	for(int i=1;i<11;i++)
	{
		if(dstc[0][i]==-1)
		{
			minSize=-1;	
			break;
		}
	}
	if(minSize==-1)
	{
		cout<<-1<<'\n';
		continue;//while 안에 있고 이줄 밑은 시랭 x
	}
		
	do
	{
		int val=0;
		for(int i=1;i<tempV.size();i++)
		{
			val+=dstc[tempV[i-1]][tempV[i]];
		}
		minSize=(minSize>val?val:minSize);
	}
	while(next_permutation(tempV.begin()+1,tempV.end()));
	
	cout<<minSize<<'\n';
}

}
void bfs(const point p,int num)//num 번째 정점부터 다른정점까지의 최소거리를 구한다
{
	int dist[22][22]={};
	dist[p.first][p.second]=1;
	queue<point> q;
	q.push(p);
	while(!q.empty())
	{
		point curNode=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			point temp=point(curNode.first+dx[i],curNode.second+dy[i]);

			if(room[temp.first][temp.second]!=0&&dist[temp.first][temp.second]==0)//갈수있고,간적이없다
			{
				dist[temp.first][temp.second]=dist[curNode.first][curNode.second]+1;
				q.push(temp);
			}

		}
	}
	for(int i=0;i<node.size();i++)
	{
		if(num!=i)
		{
			dstc[num][i]=dstc[i][num]=dist[node[i].first][node[i].second]-1;
		}
	}
}

