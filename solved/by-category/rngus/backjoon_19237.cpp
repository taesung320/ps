//상어들은 영역을 사수하기 위해 다른 상어들을 쫓아내려고 하는데, 1의 번호를 가진 어른 상어는 가장 강력해서 나머지 모두를 쫓아낼 수 있다.
//숨질뻔;;
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int sdx[401][4][4]={};
int sdy[401][4][4]={};
vector<vector<p>> arr;//바다:: (위치하는 상어 번호또는 냄새의 번호*,남은시간)
vector<vector<p>> before;
int drct[401]={};//상어의 방향
p ads[401]={};//상어들의 위치
int N,M,K;
int CNT;
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
void moveShark(int num);
void smellOnesec();//1초 지나면 냄새 하나씩 줄이기
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<N);
}
int find(int x,int y){
	for(int i=0;i<4;i++){
		if(x==dx[i]&&y==dy[i]) return i;
	}
}
int main(){
	cin>>N>>M>>K;
	arr.resize(N);
	for(int i=0;i<N;i++)
		arr[i].resize(N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			int snum;
			cin>>snum;
			if(snum){
				arr[i][j]={snum,K};
				ads[snum]={i,j};
			}
		}
	}
	for(int i=1;i<=M;i++){
		cin>>drct[i];
		drct[i]--;
	}
	for(int i=1;i<=M;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				int t;
				cin>>t;
				sdx[i][j][k]=dx[t-1];
				sdy[i][j][k]=dy[t-1];
			}
		}
	}
	int T=0;
	CNT=M;
	while(T<1000){
		before=arr;/*
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cout<<"( "<<arr[i][j].first<<" , "<<arr[i][j].second<<" )";
			}
			cout<<endl;
		}*/
		for(int i=1;i<=M;i++){
			if(ads[i].first==-1) continue;
			//움직인다.
			moveShark(i);
		}
		smellOnesec();
		
		T++;
		if(CNT==1) {
			cout<<T;
			return 0 ;
		}
	}
	cout<<-1;
	return 0;
}
void smellOnesec(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(arr[i][j].first){
				arr[i][j].second--;
				if(arr[i][j].second<=0){
					arr[i][j]={0,0};
				}
			}
		}
	}
}
void moveShark(int num){//이동, 냄새 남기기, 겹치면 밀어내거나 나가기
	int cx=ads[num].first;
	int cy=ads[num].second;
	int cd=drct[num];
	//빈칸이 있는가 없는가 ~알아서 이동
	bool goE=false;
	//cout<<num<<" :: ";
	for(int k=0;k<4;k++){
		int nx=cx+sdx[num][cd][k];
		int ny=cy+sdy[num][cd][k];
		int nd=find(sdx[num][cd][k],sdy[num][cd][k]);
		if(check(nx,ny)){
			int trgt=arr[nx][ny].first;
			if(trgt==0){
				ads[num]={nx,ny};
				arr[nx][ny]={num,K+1};
				drct[num]=nd;
				goE=true;
				//cout<<"("<<nx<<","<<ny<<") "<<"empty move\n";
				break;
			}else{
				//상어다
				if(ads[trgt].first==nx&&ads[trgt].second==ny&&before[nx][ny].first==0){
					//죽거나 죽이거나
					if(trgt>num){
						ads[num]={nx,ny};
						arr[nx][ny]={num,K+1};
						drct[num]=nd;
						goE=true;
						ads[trgt]={-1,-1};
						CNT--;
						//cout<<"killing move\n";
						break;
					}else{
						ads[num]={-1,-1};
						goE=true;
						CNT--;
						//cout<<"death move\n";
						break;
					}
				}
			}
		}
	}
	if(goE==false){
		//본인 냄새가 있는 쪽으로 이동한다
		for(int k=0;k<4;k++){
			int nx=cx+sdx[num][cd][k];
			int ny=cy+sdy[num][cd][k];
			int nd=find(sdx[num][cd][k],sdy[num][cd][k]);
			if(check(nx,ny)&&arr[nx][ny].first==num){
				ads[num]={nx,ny};
				arr[nx][ny]={num,K+1};
				drct[num]=nd;
				//cout<<"back move\n";
				break;
			}
		}
	}
}