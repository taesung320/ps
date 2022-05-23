#include<iostream>
#include<queue>
using namespace std;
const int MAX=200000;
int visited[MAX+1]={};
int dist[MAX+1]={};
int dl(int i,int x){
	if(i==0) return x-1;
	if(i==1) return x+1;
	if(i==2) return 2*x;
	return -1;
}
pair<int,int> bfs(int subin,int bro){
	queue<pair<int,int>> q;
	q.push({subin,0});
	visited[subin]=0;
	dist[subin]=1;
	while(!q.empty()){
		int cur=q.front().first;
		int tt=q.front().second;
		q.pop();
		if(cur==bro){
			return {dist[bro],visited[bro]};
		}
		for(int i=0;i<3;i++){
			int next=dl(i,cur);
			if((0<=next&&next<=MAX)){
				if(visited[next]==0){
					q.push({next,tt+1});
					visited[next]=tt+1;
					dist[next]+=dist[cur];
				}				
				else if(visited[next]==tt+1){
					dist[next]+=dist[cur];
				}
			}
		}
	}
	return{ -1,-1};
}
int main(){
	int N,M;
	cin>>N>>M;
	pair<int,int> ans=bfs(N,M);
	cout<<ans.second<<endl;
	cout<<ans.first;

}