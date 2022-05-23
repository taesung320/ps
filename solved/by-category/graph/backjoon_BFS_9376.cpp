#include<iostream>
#include<queue>
#include<utility>
#include<cstring>
#include<string>
using namespace std;
const int wall=0;
const int space=1;
const int door=2;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
typedef pair<int,int> p;
void init();
struct info{
	p firstPri;
	p secondPri;
	int doorCount=0;
}
int H,W
bool priCheck1[102][102]={};
bool priCheck2[102][102]={};
int prison[102][102]={};
queue<info> q;
int bfs();
int main(){
	int T;
	cin>>T;
	while(T--){
		init();
		cin>>H>>W;
		info temp;
		for(int i=1;i<=H;i++){
			string s;
			cin>>s;
			for(int j=0;j<s.size();j++){
				if(s[j]=='$'){
					if(temp.firstPri.first==0){
						temp.firstPri={i,j+1};
					}else{
						temp.secondPri={i,j+1};
					}
				}if(s[j]=='.'){
					prison[i][j+1]=space;
				}if(s[j]=='#'){
					prison[i][j+1]=door;
				}
			}
		}
		q.push(temp);
		int ans=bfs();
		cout<<ans<<"\n";
	}
}

void init(){
	memset(priCheck1,0,sizeof(priCheck1));
	memset(priCheck2,0,sizeof(priCheck2));
	memset(prison,0,sizeof(prison));
	queue<info> temp;
	q=temp;
}
int bfs(){
	int ans=1e9;
	while(!q.empty()){
		info cur=q.front();
		q.pop();
		bool firstArrive=false;
		bool secondArrive=false;
		if(cur.firstPri.first==1||cur.firstPri.first==H)
			firstArrive=true
		if(cur.secondPri.first==1||cur.secondPri.first==W)
			secondArrive=true;
		if(firstArrive&&secondArrive){
			ans=min(ans,cur.doorCount);
			continue;
		}
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++){
				p fp=cur.firstPri;
				p sp=cur.secondPri;
				int nextFpX=fp.first+dx[i];
				int nextFpY=fp.second+dy[i];
				int nextSpX=sp.first+dx[j];
				int nextSpY=sp.second+dy[i];
				//일단 이동 가능한가?(문은 나중에 생각)
				if((firstArrive||prison[nextFpX][nextFpY])&&(secondArrive||prison[nextSpX][nextSpY])){//도착했거나 갈수있다
					if((!firstArrive&&priCheck1[nextFpX][nextFpY])||(!secondArrive&&priCheck2[nextSpX][nextSpY]))//도착안했고 간적있다
					continue;//끝
					//간적 없으면
					info nextInfo=cur;
					if(!firstArrive)
					nextInfo.firstPri={nextFpX,nextFpY};
					if(!secondArrive&&!(nextFpX==nextSpX&&nextFpY==nextSpY))//겹치는경우 첫번째 죄수 우선
					nextInfo.secondPri={nextSpX,nextSpY};
					/*
					문을 만났을 경우
					**************문에관한 연산********************
					ㄸㄴㄹㄸㄹㄴㄸㄹㄴㄸㄹㄹㄹㄴㄸㄹ
					*/
					priCheck1[nextFpX][nextFpY]=true;
					priCheck2[nextSpX][nextSpY]=!(nextFpX==nextSpX&&nextFpY==nextSpY);
					q.push(nextInfo);
				}
			}
	}
}