//신경쓸게 너무 많다보니까... 생각 많아지는데 그냥 과감하게 쉬운건 빨리해놓고 나중에 고민하는게 좋다....
#include<iostream>
using namespace std;
#include<queue>
#include<vector>
#include<utility>
#include<iomanip>
typedef vector<vector<int>> vii;
typedef vector<vector<bool>> vbb;
typedef pair<int,int> pi;
const int EMPTY=-2;
int dc[]={0,0,-1,1};
int dr[]={1,-1,0,0};
int N,M;
vii board;
vbb stdVisit;
vii nnBoard(int N){
	vii tb(N);
	for(int i=0;i<N;i++)
		tb[i].resize(N);
	return tb;
}
vbb nnVisited(int N){
	vbb tb(N);
	for(int i=0;i<N;i++)
		tb[i].resize(N);
	return tb;
}
bool check(int r,int c){
	return (0<=r&&r<N&&0<=c&&c<N);
}
void spinBoard();
void gravityBoard();
pi bfs(int i,int j,int type);
int main(){
	cin>>N>>M;
	board=nnBoard(N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>board[i][j];
		}
	}
	int ans=0;
	while(true){
		stdVisit=nnVisited(N);
		int std_r=0;
		int std_c=0;
		int std_n=0;
		int std_m=0;
		bool groupis=false;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(board[i][j]>0){
					pi temp_p=bfs(i,j,0);//탐색하면서 무지개 개수 반환
					int temp_n=temp_p.first;
					if(temp_n<2)continue;
					groupis=true;
					int temp_m=temp_p.second;
					stdVisit[i][j]=true;
					if(temp_n>std_n){
						std_r=i;
						std_c=j;
						std_n=temp_n;
						std_m=temp_m;
						//cout<<std_r<<"  "<<std_c<<"  "<<std_m<<endl;
					}else if(temp_n==std_n){
						if(temp_m>=std_m){
							std_r=i;
							std_c=j;
							std_n=temp_n;
							std_m=temp_m;
						}
						//cout<<std_r<<"  "<<std_c<<"  "<<std_m<<endl;
					}
				}
			}
		}
		if(groupis==false) break;
		pi tmp=bfs(std_r,std_c,1);
		int num=tmp.first;
		ans+=(num*num);
		gravityBoard();
		spinBoard();
		gravityBoard();
	}
	cout<<ans<<endl;
}
pi bfs(int i,int j,int type){
	//type:0 return cnt of rainbow
	//type:1 deleteGroup and return cnt of block
	int color=board[i][j];
	vbb visited=nnVisited(N);
	queue<pi> q;
	q.push({i,j});
	visited[i][j]=true;
	int ret_m=0;
	int ret_n=0;
	while(!q.empty()){
		int cr=q.front().first;
		int cc=q.front().second;
		q.pop();
		ret_n++;
		if(type==0&&board[cr][cc]==0){
			ret_m++;
		}else if(type==1){
			board[cr][cc]=EMPTY;
		}
		for(int k=0;k<4;k++){
			int nr=cr+dr[k];
			int nc=cc+dc[k];
			if(type==0&&check(nr,nc)&&stdVisit[nr][nc]==true&&board[nr][nc]==color){
				return {-1,-1};
			}
			if(check(nr,nc)&&visited[nr][nc]==false
			   &&(board[nr][nc]==0||board[nr][nc]==color)){
				q.push({nr,nc});
				visited[nr][nc]=true;
			}
		}
	}
	if(type==0)
		return {ret_n,ret_m};
	else if(type==1)
		return {ret_n,0};
}
void spinBoard(){
	vii tempv=nnBoard(N);
	for(int i=N-1;i>=0;i--){
		for(int j=0;j<N;j++){
			tempv[(N-1-i)][j]=board[j][i];
		}
	}
	board=tempv;
	return ;
}
void gravityBoard(){
	for(int i=N-2;i>=0;i--){
		for(int j=0;j<N;j++){
			int cr=i;
			int cc=j;
			int cb=board[cr][cc];
			if(cb==-1) continue;
			board[cr][cc]=EMPTY;
			while(check(cr,cc)&&board[cr][cc]==EMPTY){
				cr++;
			}
			cr--;
			board[cr][cc]=cb;
		}
	}
}