#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> node;
int F, S, G, U, D;
int bfs(){
	bool visited[1000001]={};
	queue<node> q;
	q.push({S,0});
	visited[S]=true;
	while(!q.empty()){
		int cur=q.front().first;
		int cnt=q.front().second;
		q.pop();
		if(cur==G) return cnt;
		vector<int> next;
		if((cur+U)<=F) next.push_back(cur+U); 
		if((cur-D)>=1) next.push_back(cur-D);
		for(int k=0;k<next.size();k++){
			if(!visited[next[k]])
			{
				visited[next[k]]=true;
				q.push({next[k],cnt+1});
			}
		}
	}
	return -1;
}
int main(){
	cin>>F>>S>>G>>U>>D;
	int ans=bfs();
	if(ans==-1) cout<<"use the stairs";
	else cout<<ans;
}