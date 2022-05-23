#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<cstring>
using namespace std; 
typedef pair<int,int> pir;
int N,M;
int arr[51][51]={};
bool visited[51][51]={};
bool check(int i=0,int j=0){
	return (0<=i&&i<N&&0<=j&&j<M)&&(!visited[i][j]);
}
pir dxy[]={{0,-1},{-1,0},{0,1},{1,0}};
vector<pir> nxtD[51][51];

void nextD(int i,int j){

	for(int k=0;k<4;k++){
		if(!((1<<k)&arr[i][j])){
			nxtD[i][j].push_back(dxy[k]);
		}
	}
}

int bfs(int i,int j,bool type);
int main(){
	cin>>M>>N;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
		}
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			nextD(i,j);
		}
	}
	int no1_ans=0;
	int no2_ans=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(visited[i][j]==false){
				no1_ans++;
				no2_ans=max(no2_ans,bfs(i,j,0));
			}
		}
	}
	int no3_ans=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			for(int k=0;k<4;k++){
				if((1<<k)&arr[i][j]){
					nxtD[i][j].push_back(dxy[k]);
					no3_ans=max(no3_ans,bfs(i,j,1));
					nxtD[i][j].pop_back();
				}
			}
		}
	}
	cout<<no1_ans<<"\n"
		<<no2_ans<<"\n"
		<<no3_ans;
}
int bfs(int i,int j,bool type){
	if(type==true){
		memset(visited,0,sizeof(visited));
	}
	queue<pir> q;
	q.push({i,j});
	visited[i][j]=true;
	int wth=1;
	while(!q.empty()){
		int hi=q.front().first;
		int hj=q.front().second;
		q.pop();
		vector<pir> nxy=nxtD[hi][hj];
		for(int i=0;i<nxy.size();i++){
			int ni=hi+nxy[i].first;
			int nj=hj+nxy[i].second;
			if(check(ni,nj)){
				visited[ni][nj]=true;
				q.push({ni,nj});
				wth++;
			}
		}
	}
	return wth;
}


