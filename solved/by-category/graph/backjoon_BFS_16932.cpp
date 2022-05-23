#include<iostream>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int arr[1000][1000]={};
int num[1000000]={};
int par[1000000]={};
int N,M;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int visited[1000][1000]={};
int xy2i(int x,int y){
	return x*1000+y;
}
p i2xy(int i){
	return {i/1000,i%1000};
}
int find(int x){
	if(x==par[x]) return x;
	else return par[x]=find(par[x]);
}
void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx==fy) return;
	else{
		par[fy]=fx;
	}
}
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<M)&&arr[x][y];
}
void bfs(int x,int y){
	visited[x][y]=true;
	queue<p> q;
	q.push({x,y});
	num[find(xy2i(x,y))]=1;
	while(!q.empty()){
		int cx=q.front().first;
		int cy=q.front().second;
		q.pop();
		for(int k=0;k<4;k++){
			int nx=cx+dx[k];
			int ny=cy+dy[k];
			if(check(nx,ny)&&arr[nx][ny]&&!visited[nx][ny]){
				visited[nx][ny]=true;
				merge(xy2i(cx,cy),xy2i(nx,ny));
				num[find(xy2i(cx,cy))]++;
				q.push({nx,ny});
			}
		}
	}
}
int getSumfd(int i,int j){
	int ret=1;
	vector<int> v;
	for(int k=0;k<4;k++){
		int tx=i+dx[k];
		int ty=j+dy[k];
		int dd=num[find(xy2i(tx,ty))];
		for(int s=0;s<v.size();s++){
			if(v[s]==find(xy2i(tx,ty))){
				dd=0;break;
			}
		}
		if(dd){
			ret+=dd;
			v.push_back(find(xy2i(tx,ty)));
		}
	}
	return ret;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
	cin>>N>>M;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
			par[xy2i(i,j)]=xy2i(i,j);
		}
	}
	int ans=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(arr[i][j]&&!visited[i][j])
				bfs(i,j);
		}
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(arr[i][j]==0){
				ans=max(ans,getSumfd(i,j));
			}
			cout<<num[find(xy2i(i,j))]<<" ";
		}
		cout<<endl;
	}
	cout<<ans;
}