#include<iostream>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int ans=0;
int dx[]={0,-1,-1,0,1,1,1,0,-1};
int dy[]={0,0,-1,-1,-1,0,1,1,1};
bool check(int x,int y){
	return (0<=x&&x<4&&0<=y&&y<4);
}
void moveFish(vector<vector<p>>& arr,vector<p>& ads){
	for(int i=1;i<=16;i++){
		if(ads[i].first==-1) continue;
		int cx=ads[i].first;
		int cy=ads[i].second;
		int cd=arr[cx][cy].second;
		while(true){
			if(cd==0){
				cd++;
				continue;
			} 
			int nx=cx+dx[cd];
			int ny=cy+dy[cd];
			if(check(nx,ny)&&arr[nx][ny].first!=17){
				int d=arr[nx][ny].second;
				int f=arr[nx][ny].first;
				//위치변경
				ads[f]={cx,cy};
				ads[i]={nx,ny};
				//방향변경,번호변경
				arr[cx][cy]={f,d};
				arr[nx][ny]={i,cd};
				break;
			}
			cd=(cd+1)%9;
		}
		
	}
}
void moveShark(vector<vector<p>> arr,vector<p> ads,int cnt){
	
	bool ate=false;
	int sx=ads[17].first;
	int sy=ads[17].second;
	//cout<<sx<<" , "<<sy<<" curCnt--> "<<cnt<<endl;
	int sd=arr[sx][sy].second;
	arr[sx][sy].first=0;
	while(check(sx=sx+dx[sd],sy=sy+dy[sd])){
		if(arr[sx][sy].first==0) continue;
		ate=true;
		vector<vector<p>> tempArr=arr;
		vector<p> tempAds=ads;
		int trgt=tempArr[sx][sy].first;
		tempAds[trgt]={-1,-1};
		tempAds[17]={sx,sy};
		tempArr[sx][sy].first=17;
		moveFish(tempArr,tempAds);
		//cout<<"-----nextCnt--> "<<cnt+trgt<<endl;
		moveShark(tempArr,tempAds,cnt+trgt);
	}
	if(ate==false){
		ans=max(ans,cnt);
	}
}

int main(){
	vector<vector<p>> arr(4);
	vector<p> ads(18);//17번 : 상어
	int zz;
	for(int i=0;i<4;i++){
		arr[i].resize(4);
		for(int j=0;j<4;j++){
			int f,s;
			cin>>f>>s;
			arr[i][j]={f,s};
			ads[f]={i,j};
			if(i==0&&j==0)
				zz=f;
		}
	}
	ads[zz]={-1,-1};
	ads[17]={0,0};
	arr[0][0].first=17;
	//상어진입하고 시작
	moveFish(arr,ads);
	moveShark(arr,ads,zz);
	cout<<ans;
}