#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> p;
bool arr[1002][1002]={};
bool visited[1002][1002]={};
int ans[1002][1002]={};
int nei[1002][1002]={};
p par[1002][1002]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool isSame(p p1,p p2){
	return (p1.first==p2.first&&p1.second==p2.second);
}
p find(p pnt){
	p& ppnt=par[pnt.first][pnt.second];
	if(isSame(pnt,ppnt))
		return pnt;
	else
		return ppnt=find(ppnt);
}
void merge(p p1,p p2){
	p1=find(p1);
	p2=find(p2);
	if(isSame(p1,p2)) return ;
	else{
		par[p2.first][p2.second]=p1;
	}
}
////////////////////////////////////////////////
int getFourDirSum(int x,int y){
	vector<p> temp;
	for(int i=0;i<4;i++){
		p np=find({x+dx[i],y+dy[i]});
		int vs=temp.size();
		for(int j=0;j<vs+1;j++){
			if(j==vs){
				temp.push_back(np);
			}
			else{
				if(isSame(find(np),find(temp[j])))
					break;
			}
		}
	}
	int ret=0;
	for(int i=0;i<temp.size();i++){
		ret+=nei[temp[i].first][temp[i].second];
	}
	return ret;
}
void dfs(int x,int y){//return 될 때는 이미 ans[x][y]가 정의되어있다
	visited[x][y]=true;
	p fxy=find({x,y});
	int& curNei=nei[fxy.first][fxy.second];
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(arr[nx][ny]&&!visited[nx][ny]){
			dfs(nx,ny);
			p nFxy=find({nx,ny});
			curNei+=nei[nFxy.first][nFxy.second];
			merge(fxy,nFxy);
		}
	}
	return ;
}

int main(){
	int N,M;
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		string s;
		cin>>s;
		for(int j=0;j<s.size();j++){
			if(s[j]=='0'){
				arr[i][j+1]=true;
				nei[i][j+1]=1;
			}
			par[i][j+1]={i,j+1};
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(arr[i][j]){
				dfs(i,j);
			}
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(!arr[i][j]){
				ans[i][j]=getFourDirSum(i,j);
			}
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			if(!arr[i][j])
				cout<<(ans[i][j]+1)%10;
			else
				cout<<0;
		}
		cout<<"\n";
	}
}