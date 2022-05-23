#include<iostream>
#include<cstring>
#include<utility>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> point;
typedef pair<point,int> node;
struct dxy{
	point d;
	int cost;
};
vector<dxy> dt[3];
int N,M;
int night,bis,look;
int arr[50][50]={};
int nightx[]={-1,-2,-2,-1,1,2,1,2};
int nighty[]={-2,-1,1,2,-2,-1,2,1};
int dx[]={0,0,1,-1,1,1,-1,-1};
int dy[]={1,-1,0,0,1,-1,1,-1};
int dist[50][50][1<<4]={};
const int INF=1e9;
bool check(int x,int y,int m){
	return ((0<=x&&x<N&&0<=y&&y<N)&&0<=m&&m<(1<<M));
}
int dik(int x,int y){
	priority_queue<pair<int,node>,vector<pair<int,node>>,greater<pair<int,node>>> pq;
	pq.push({0,{{x,y},0}});
	dist[x][y][0]=0;
	while(!pq.empty()){
		node cur=pq.top().second;
		int cost=pq.top().first;
		pq.pop();
		if(cur.second==((1<<M)-1))
			return cost;
		for(int i=0;i<3;i++){
			for(int j=0;j<dt[i].size();j++){
				int nx=cur.first.first+dt[i][j].d.first;
				int ny=cur.first.second+dt[i][j].d.second;
				int nm=cur.second;
				int nc=dt[i][j].cost;
				if(!check(nx,ny,nm))
					continue;
				if(arr[nx][ny]!=-1){
					if(!(nm&(1<<arr[nx][ny]))){
						nm+=(1<<arr[nx][ny]);
					}
				}
				if(dist[nx][ny][nm]>cost+nc){
					dist[nx][ny][nm]=cost+nc;
					pq.push({dist[nx][ny][nm],{{nx,ny},nm}});
				}
			}
		}
	}
}
int main(){
	memset(arr,-1,sizeof(arr));
	cin>>N;
	cin>>night>>bis>>look;
	//오리 좌표
	int x,y;
	cin>>x>>y;
	cin>>M;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<(1<<M);k++){
				dist[i][j][k]=INF;
			}
		}
	}
	for(int i=0;i<M;i++){
		int fx,fy;
		cin>>fx>>fy;
		arr[fx][fy]=i;
	}
	for(int i=0;i<8;i++){
		dxy temp;
		temp.d={nightx[i],nighty[i]};
		temp.cost=night;
		dt[0].push_back(temp);
	}
	for(int j=0;j<8;j++){
		for(int i=1;i<N;i++){
			dxy temp;
			temp.d={i*dx[j],i*dy[j]};
			temp.cost=(j<4?look:bis);
			int xx=(j<4?1:2);
			dt[xx].push_back(temp);
		}	
	}
	int ans=dik(x,y);
	cout<<ans;
}