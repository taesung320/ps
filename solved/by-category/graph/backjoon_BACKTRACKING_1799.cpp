#include<iostream>
using namespace std;

int board[10][10]={};
int field[10][10]={};
int N;
void solve(int cnt);
int dx[]={1,1,-1,-1};
int dy[]={-1,1,-1,1};
void printBoard(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<field[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool check(int x,int y){
	return (0<=x&&0<=y&&x<N&&y<N);
}
void bishop(int i,int j,int set){
	field[i][j]+=set;
	for(int x=0;x<4;x++){
		int ti=i;
		int tj=j;
		while(check(ti+=dx[x],tj+=dy[x])){
			field[ti][tj]+=set;
		}
	}
}
int ans=0;
int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>board[i][j];
		}
	}
	solve(0);
	cout<<ans;
}
void solve(int cnt){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(board[i][j]==1&&field[i][j]==0){
				ans=max(ans,cnt+1);
				//int x;
				///;cin>>x;
				//cout<<i<<" , "<<j<<"))-->"<<ans<<endl;
				//d이곳을 기점으로 비숍의 영역 체크
				//>>
				bishop(i,j,2);
				//printBoard();
				solve(cnt+1);
				//d이곳을 기점으로 체크된 영역 해재
				//>>
				bishop(i,j,-2);
			}
		}
	}
}