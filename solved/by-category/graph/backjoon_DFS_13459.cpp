#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
typedef pair<int,int> pnt;
typedef pair<bool,bool> rb;
bool arr[12][12]={};
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
string ds[]={"U","D","L","R"};
int ans=12;
string ansString="";
pnt hole;
bool visited[12][12][12][12]={};
bool isSame(pnt a,pnt b){
	return (a.first==b.first&&b.second==a.second);
}
bool isHole(pnt p ){
	return isSame(p,hole);
}
pnt nextPoint(pnt p,int x){//움직이고 멈춘결과 반환, 구멍만나면 구멍반환
	int px=p.first;
	int py=p.second;
	while(arr[px][py]){
		if(isHole({px,py})){
			return {px,py};
		}
		if(arr[px+dx[x]][py+dy[x]]){
			px+=dx[x];
			py+=dy[x];
		}else{
			break;
		}
	}
	return {px,py};
}
void dfs(pnt R,pnt B,int cnt,string curs){//R,B에서 구멍까지의 최소움직임 을 반환한다
	//cout<<" R point::( "<<R.first<<" , "<<R.second<<" )";
	//cout<<"B point::( "<<B.first<<" , "<<B.second<<" )\n---------"<<endl;
	bool rh=isHole(R);
	bool bh=isHole(B);
	if(cnt>=ans) return ;
	if(rh||bh){
		if(bh) return ;
		else {
			if(ans>cnt){
				ans=cnt;
				ansString=curs;
			}
			return ;
		}
	}
	int rx=R.first;
	int ry=R.second;
	int bx=B.first;
	int by=B.second;
	visited[rx][ry][bx][by]=true;
	for(int i=0;i<4;i++){
		pnt nextR=nextPoint(R,i);
		pnt nextB=nextPoint(B,i);
		if(isSame(nextR,nextB)&&!isHole(nextR)){
			if((i==0&&(R.first<B.first))||(i==1&&(R.first>B.first))||((i==2)
				&&(R.second<B.second)||(i==3)&&(R.second>B.second))){//R이 먼저 출발한 경우	
				nextB.first-=dx[i];
				nextB.second-=dy[i];
			}
			else{//B가 먼저 출발한 경우
				nextR.first-=dx[i];
				nextR.second-=dy[i];
			}
		}	
		if(!visited[nextR.first][nextR.second][nextB.first][nextB.second]){
			dfs(nextR,nextB,cnt+1,curs+ds[i]);
		}
	}
	visited[rx][ry][bx][by]=false;
	return ;
}
int main(){
	int N,M;
	cin>>N>>M;
	pnt R,B;
	for(int i=1;i<=N;i++){
		string s;
		cin>>s;
		for(int j=0;j<s.size();j++){
			if(s[j]=='B'){
				B={i,j+1};	
				arr[i][j+1]=true;
			}else if(s[j]=='R'){
				R={i,j+1};
				arr[i][j+1]=true;
			}else if(s[j]=='O'){
				arr[i][j+1]=true;
				hole={i,j+1};
			}else if(s[j]=='.'){
				arr[i][j+1]=true;
			}
		}
	}
	string s="";
	dfs(R,B,0,s);
	cout<<ans<<endl;
	cout<<ansString<<endl;
}