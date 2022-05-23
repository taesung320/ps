#include<iostream>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
typedef vector<vector<int>> vv;
int N;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<N);
}
vector<bool> asdasd(11);
string msg[]={"go right","go left","go up","go down"};
int ans=0;
int find_max(vv v){
	int ret=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			ret=max(ret,v[i][j]);
		}
	}
	return ret;
}
map<vv,int> mM;
pair<vv,int> move(vv v,int dirc){
	/*//
	cout<<"--------------------\n";
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	int x;
	cin>>x;
	cout<<endl;
	cout<<msg[dirc]<<endl;
	cout<<endl;
	//*///
	bool isChanged=false;
	bool merged[20][20]={};
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			int cx,cy;
				if(dirc==0){
					cx=j;
					cy=N-i-1;
				}else if(dirc==1){
					cx=j;
					cy=i;
				}else if(dirc==2){
					cx=i;
					cy=j;
				}else if(dirc==3){
					cx=N-i-1;
					cy=j;
				}
			/*//
			if(dirc==2)
				cout<<cx<<" , "<<cy<<endl;
			*///
			int startNum=v[cx][cy];
			int save_cx=cx;
			int save_cy=cy;
			v[save_cx][save_cy]=0;//이전것은 0
			while(true){//nx,ny 결정
				int nx=cx+dx[dirc];
				int ny=cy+dy[dirc];
					if(check(nx,ny)){//이동 가능일때
						if(v[nx][ny]==0){
							cx=nx;
							cy=ny;//한칸씩 전진
						}else{
							//숫자와 만났다 == 정지
							if(merged[nx][ny]==false&&startNum==v[nx][ny]){
								merged[nx][ny]=true;
								v[nx][ny]*=2;//흡수
							}else{
								nx-=dx[dirc];
								ny-=dy[dirc];
								v[nx][ny]=startNum;//앞에 멈춤
							}
							break;
						}
					}else{//더이상 이동불가일때
						nx-=dx[dirc];
						ny-=dy[dirc];
						v[nx][ny]=startNum;
						break;
					}
			}if(v[save_cx][save_cy]!=startNum){
				isChanged=true;
			}
		}
	}
	/*//
	cout<<(isChanged?"changed!\n":"noChanged!\n");
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"--------------------\n";
	//*///
	if(isChanged)
		return {v,1};
	else
		return {v,0};
}
void fnc(vv v,int cnt){
	ans=max(ans,find_max(v));
	if(cnt==10){
		return;
	}
	for(int i=0;i<4;i++){
		pair<vv,int> tmp=move(v,i);
		vv nextV=tmp.first;
		
		if(tmp.second){
			int next_val=find_max(nextV);
			int k=10-cnt;//대충 남은횟수
			if(ans<next_val*pow(2,k))
				fnc(nextV,cnt+1);
		}
	}
}
int main(){
	cin>>N;
	vv v(N);
	for(int i=0;i<v.size();i++)
		v[i].resize(N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>v[i][j];
		}
	}
	fnc(v,0);
	cout<<ans;
}