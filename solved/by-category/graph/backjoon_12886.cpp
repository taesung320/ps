#include<iostream>
#include<queue>
#include<vector>
using namespace std;
bool visited[501][501]={};
int sum=0;
int ans=0;
bool check(vector<int> t){
	for(int i=0;i<t.size();i++){
		if(1<=t[i]&&t[i]<=500){
			continue;
		}else{
			return false;
		}
	}
	return true;
}
void dfs(int a,int b){
	vector<int> t={a,b,sum-a-b};
	if(ans==1) return;
	if(t[0]==t[1]&&t[1]==t[2]){
		ans=1;
		return;
	}
	for(int i=0;i<t.size();i++){
		for(int j=i+1;j<t.size();j++){
			if(t[i]==t[j]) continue;
			vector<int> next_t=t;
			int x_idx,y_idx;
			if(t[i]<t[j]){
				x_idx=i;
				y_idx=j;
			}else{
				x_idx=j;
				y_idx=i;
			}
			next_t[x_idx]=(t[x_idx]*2);
			next_t[y_idx]=(t[y_idx]-t[x_idx]);
			if(check(next_t)&&visited[next_t[0]][next_t[1]]==false){
				for(int ii=0;ii<3;ii++){
					for(int jj=0;jj<3;jj++){
						if(ii!=jj)
						visited[next_t[ii]][next_t[jj]]=true;
					}
				}
				dfs(next_t[0],next_t[1]);
			}
		}
	}
}
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	sum=a+b+c;
	if(sum%3){
		cout<<"0";return 0;
	}
	visited[a][b]=true;
	vector<int> t={a,b,sum-a-b};
	for(int ii=0;ii<3;ii++){
		for(int jj=0;jj<3;jj++){
			if(ii!=jj)
				visited[t[ii]][t[jj]]=true;
		}
	}
	dfs(a,b);
	cout<<ans;
}










