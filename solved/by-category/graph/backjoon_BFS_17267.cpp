#include<iostream>
#include<queue>
#include<algorithm>
#include<string>
#include<utility>
using namespace std;
typedef pair<int,int> pi;
typedef pair<pi,pi> pipi;
int N,M,L,R;
string s;
int arr[1002][1002]={};
bool vst[1002][1002]={};
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
pipi stt;
int getAns(){
	queue<pipi> q;
	q.push(stt);
	int cnt=1;
	while(!q.empty()){
		pipi curP=q.front();q.pop();
		pi cur=curP.first;
		pi lrState=curP.second;
		for(int i=0;i<4;i++){
			int nextX=cur.first+dx[i];
			int nextY=cur.second+dy[i];
			if(dy[i]==1){
				nextY=min(nextY,cur.second+lrState.second);
			}
			else if(dy[i]==-1){
				nextY=max(nextY,cur.second-lrState.first);
			}
			else{
				int nextnextX=nextX;
				while(!vst[nextnextX][nextY]&&arr[nextnextX][nextY]){
					cnt++;
					vst[nextnextX][nextY]=true;
					q.push({{nextnextX,nextY},lrState});
					nextnextX+=dx[i];
				}
			}
			if(!vst[nextX][nextY]&&arr[nextX][nextY]){
				cnt++;
				vst[nextX][nextY]=true;
				pi nextLrState=lrState;
				if(dy[i]==1)
					nextLrState.second-=1;
				else if(dy[i]==-1)
					nextLrState.first-=1;
				q.push({{nextX,nextY},nextLrState});
				//cout<<"( "<<nextX<<" , "<<nextY<<" )"<<endl;
			}
		}
	}
	return cnt;
}
int main(){
	cin>>N>>M>>L>>R;
	for(int i=1;i<=N;i++){
		cin>>s;
		for(int j=0;j<s.size();j++){
			if(s[j]=='2'){
				pi& start=stt.first;
				start.first=i;
				start.second=j+1;
				vst[start.first][start.second]=true;
				pi& lr=stt.second;
				lr.first=L;
				lr.second=R;
				arr[i][j+1]=1;
			}
			else
				arr[i][j+1]=(s[j]=='0'?1:0);
		}
	}
	int ans=getAns();
	cout<<ans;
}
