#include<iostream>
#include<cstring>
using namespace std;
int N;
int arr[32][32]={};
long long int cache[32][32][3]={};
bool check(int x,int y){
	return (0<=x&&x<N&&0<=y&&y<N)&&(arr[x][y]==0);
}
long long int DP(int x,int y,int s){
	if(s==1){
		if(!(check(x,y)&&check(x-1,y)&&check(x,y-1))) return 0;
	}else{
		if(!check(x,y)) return 0;
	}
	if(x==N-1&&y==N-1) return 1;
	long long int& ret=cache[x][y][s];
	if(ret!=-1) return ret;
	if(s==0){
		ret=DP(x,y+1,0)+DP(x+1,y+1,1);
	}else if(s==1){
		ret=DP(x+1,y+1,1)+DP(x+1,y,2)+DP(x,y+1,0);
	}else{
		ret=DP(x+1,y,2)+DP(x+1,y+1,1);
	}
	return ret;
}

int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>arr[i][j];
		}
	}
	memset(cache,-1,sizeof(cache));
	cout<<DP(0,1,0);
}