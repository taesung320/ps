#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<queue>
using namespace std;
typedef vector<vector<char>> hni;
typedef pair<hni,int> hq;
set<hni> m; 
queue<hq> q;
bool isMono(hni h);
int bfs();
int main(){
	hni start(3);
	for(int i=0;i<3;i++){
		int a;
		string s;
		cin>>a;
		if(a==0) continue;
		cin>>s;
		for(int j=0;j<s.size();j++){
			start[i].push_back(s[j]);
		}
	}
	q.push({start,0});
	m.insert(start);
	int ans=bfs();
	cout<<ans;
}
int bfs(){
	while(!q.empty()){
		hni cur=q.front().first;
		int curN=q.front().second;
		q.pop();
		if(isMono(cur)) return curN;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				hni next=cur;
				if(next[i].empty()||i==j) continue;
				char ichar=next[i].back();
				next[i].pop_back();
				next[j].push_back(ichar);
				if(m.find(next)==m.end()){
					m.insert(next);
					q.push({next,curN+1});
				}
			}
		}
	}
	return 0;
}
bool isMono(hni h){
	char t[3]={'A','B','C'};
	bool ret=true;
	for(int i=0;i<3;i++){
		while(!h[i].empty()){
			if(h[i].back()!=t[i])
				return false;
			h[i].pop_back();
		}
	}
	return ret;
}