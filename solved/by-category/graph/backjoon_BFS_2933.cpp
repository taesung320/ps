#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<algorithm>
#include<utility>
using namespace std;
typedef pair<int,int> p;
string mi[101]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int R,C;
void bfsOnce(int lr,int h);
void breaked(int lr,int h);
void fallmi(vector<p> v,int m);
bool check(int h,int w){
	return (1<=h&&h<=R&&0<=w&&w<C);
}
int main(){
	cin>>R>>C;
	for(int i=1;i<=R;i++){
		cin>>mi[i];
	}
	int M;
	cin>>M;
	for(int i=0;i<M;i++){
		int h;
		cin>>h;
		bfsOnce(i%2,h);
	}
	for(int k=1;k<=R;k++){
		cout<<mi[k]<<"\n";
	}
}
void bfsOnce(int rl,int h){
	breaked(rl,h);
	queue<p> q;
	vector<p> clst;
	bool visited[102][102]={};
	int x=R;
	for(int y=0;y<C;y++){
		if(mi[x][y]=='.') continue;
		q.push({x,y});
		visited[x][y]=true;
	}
	while(!q.empty()){
		int ch=q.front().first;
		int cw=q.front().second;
		q.pop();
		for(int k=0;k<4;k++){
			int nh=ch+dx[k];
			int nw=cw+dy[k];
			if(check(nh,nw)&&!visited[nh][nw]&&mi[nh][nw]=='x'){
				visited[nh][nw]=true;
				q.push({nh,nw});
			}
		}
	}
	for(int i=1;i<=R;i++){
		for(int j=0;j<C;j++){
			if(mi[i][j]=='x'&&visited[i][j]==false) clst.push_back({i,j});
		}
	}
	int move=1e9;
	for(int i=0;i<clst.size();i++){
		int ch=clst[i].first;
		int cw=clst[i].second;
		int falldown=0;	
		while(true){
			ch++;
			falldown++;
			if(ch>R||(mi[ch][cw]=='x'&&visited[ch][cw])){
				move=min(move,falldown-1);
				break;
			}
			if(mi[ch][cw]=='x'&&!visited[ch][cw]) break;
		}
	}
	if(move==0) return ;
	fallmi(clst,move);
	return ;
}
void breaked(int lr,int h){
	int start=(lr==0?0:C-1);
	int end=(lr==1?0:C-1);
	int di=(lr==0?1:-1);
	for(int i=start;((lr==0&&i<=end)||(lr==1&&i>=end));i+=di){
		if(mi[R-h+1][i]=='x'){
			mi[R-h+1][i]='.';
			return;
		}
	}
}
void fallmi(vector<p> v,int m){
	sort(v.begin(),v.end());
	for(int i=v.size()-1;i>=0;i--){
		int ch=v[i].first;
		int cw=v[i].second;
		mi[ch][cw]='.';
		mi[ch+m][cw]='x';
	}
}
   