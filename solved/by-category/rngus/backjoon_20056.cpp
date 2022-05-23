#include<iostream>
#include<vector>
#include<utility>
using namespace std;
struct fireball{
	int m,s,d;
	fireball(int _m=0,int _s=0,int _d=0):m(_m),s(_s),d(_d){};
};
int N,M,K;
int dr[]={-1,-1,0,1,1,1,0,-1};
int dc[]={0,1,1,1,0,-1,-1,-1};
typedef pair<int,int> p;
typedef vector<vector<vector<fireball>>> Board;
Board board;
Board n_by_n_board(int N){
	Board board(N);
	for(int i=0;i<N;i++){
		board[i].resize(N);
	}
	return board;
}
void moveFire();
void splitFire();
int main(){
	cin>>N>>M>>K;
	board=n_by_n_board(N);
	for(int i=0;i<M;i++){
		int r,c,m,s,d;
		cin>>r>>c>>m>>s>>d;
		board[r-1][c-1].push_back(fireball(m,s,d));
	}
	while(K--){
		//move 
		moveFire();
		splitFire();
	}
	int ans=0;
	for(int i=0;i<board.size();i++){
		for(int j=0;j<board[i].size();j++){
			for(int k=0;k<board[i][j].size();k++){
				ans+=board[i][j][k].m;
			}
		}
	}
	cout<<ans;
}
void moveFire(){
	Board tempBoard=n_by_n_board(N);
	for(int i=0;i<board.size();i++){
		for(int j=0;j<board[i].size();j++){
			for(int k=0;k<board[i][j].size();k++){
				fireball fb=board[i][j][k];
				int d=fb.d;
				int s=fb.s;
				int nr=((i+s*dr[d])%N+N)%N; // 이거 약간 의미있는 한줄.
				int nc=((j+s*dc[d])%N+N)%N; 
				tempBoard[nr][nc].push_back(fb);
			}
		}
	}
	board=tempBoard;
}
void splitFire(){
	for(int i=0;i<board.size();i++){
		for(int j=0;j<board[i].size();j++){
			if(board[i][j].size()<=1) continue;
			int sum_s=0;
			int sum_m=0;
			bool isSame=true;
			int stnd=board[i][j][0].d%2;
			for(int k=0;k<board[i][j].size();k++){
				fireball fb=board[i][j][k];
				sum_s+=fb.s;
				sum_m+=fb.m;
				if(isSame){
					isSame=(fb.d%2==stnd);
				}
			}
			int next_s=sum_s/board[i][j].size();
			int next_m=sum_m/5;
			vector<fireball> tempFb;
			if(next_m){
				for(int k=0;k<4;k++){
					tempFb.push_back(fireball(next_m,next_s,k*2+(isSame?0:1)));
				}	
			}
			board[i][j]=tempFb;
		}
	}
}