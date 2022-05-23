#include<iostream>
#include<queue>
#include<utility>
using namespace std;
typedef priority_queue<int,vector<int>,greater<int>> ipq;
typedef pair<int,ipq> info;// <다 죽게됐을때 양분 , pq >
info grd[11][11]={};
int A[11][11]={};
int arr[11][11]={};
int five[11][11]={};
int dx[]={1, 1,0, 0,-1,1,-1,-1};
int dy[]={1,-1,1,-1, 0,0,-1, 1};
void ss_season();
void fw_season();
void breed8mile(int i,int j,int n);
int N,M,K;
int main(){

	cin>>N>>M>>K;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			cin>>A[i][j];
			arr[i][j]=5;
		}
	}
	for(int i=0;i<M;i++){
		int r,c,age;
		cin>>r>>c>>age;
		if(age%5==0){
			five[r][c]++;
		}
		grd[r][c].first+=age/2;
		grd[r][c].second.push(age);
	}
	while(K--){
		ss_season();
		fw_season();
	}
	int ans=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			ans+=grd[i][j].second.size();
		}
	}
	cout<<ans;
}
void ss_season(){
	int dead[11][11]={};
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			int cur_a=grd[i][j].first; // 다 죽었을때 양분이 될거
			ipq cur_trees=grd[i][j].second; // 나무들
			
			int next_a=0;
			ipq next_trees;
			
			int cur_five=five[i][j]; //5배수 개수
			int next_five=0;
			
			while(!cur_trees.empty()){
				int yst=cur_trees.top();
				cur_trees.pop();// 가장 어린 나무
				cur_a-=(yst/2);
				
				if(yst<=arr[i][j]){//영양이 있다
					arr[i][j]-=yst;
					next_a+=(yst+1)/2;
					if((yst+1)%5==0){
						next_five++;
					}
					next_trees.push(yst+1);
				}else{//영양이 없다 -> 싹다 죽는다~영양
					arr[i][j]+=(cur_a+(yst/2));
					break;
				}
			}
			five[i][j]=next_five;
			grd[i][j]={next_a,next_trees};
		}
	}
}
void fw_season(){
	//fall
		//5배수인 것들의 좌표를 어찌 찾을까????
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(five[i][j]){
				breed8mile(i,j,five[i][j]);
			}
		}
	}
	//wintre
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			arr[i][j]+=A[i][j];
		}
	}
}
void breed8mile(int i,int j,int n){
	while(n--){
	for(int k=0;k<8;k++){
		grd[i+dx[k]][j+dy[k]].second.push(1);
	}
	}
}