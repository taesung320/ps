#include<iostream>
#include<vector>
using namespace std;
//포인터 사용하는 시도 낫베드, 런타임 에러 대처하는법 베드(이건 자신감 부족+덜렁이)
vector<vector<int>> arr;
int N,M,K;
int ans=1e9;
struct rcs{
	int r;
	int c;
	int s;
	rcs(int r=0,int c=0,int s=0){
		this->r=r;
		this->c=c;
		this->s=s;
	}
};
vector<rcs> mv;
void doSpin(vector<vector<int>>& arr,int r,int c,int s){
	int r1=r-s;int c1=c-s;int r2=r+s;int c2=c+s;
	if(s==0) return ;
	vector<int*> vec;
	for(int i=c1;i<=c2;i++)
		vec.push_back(&arr[r1][i]);
	for(int i=r1;i<=r2;i++)
		vec.push_back(&arr[i][c2]);
	for(int i=c2;i>=c1;i--)
		vec.push_back(&arr[r2][i]);
	for(int i=r2;i>r1;i--)
		vec.push_back(&arr[i][c1]);
	int temp=*vec[vec.size()-1];
	for(int i=vec.size()-2;i>=0;i--){
		*vec[i+1]=*vec[i];
	}
	*vec[0]=temp;
	doSpin(arr,r,c,s-1);
}
int getVal(vector<vector<int>> arr){
	int ret=1e9;
	//cout<<endl;
	for(int i=1;i<=N;i++){
		int rowSum=0;
		for(int j=1;j<=M;j++){
			rowSum+=arr[i][j];
			//cout<<arr[i][j];
		}
		ret=min(ret,rowSum);
		//cout<<endl;
	}
	return ret;
}
void getMinVal(vector<vector<int>> arr,vector<bool> com,int cnt);
int main(){
	cin>>N>>M>>K;
	arr.resize(N+1);
	for(int i=0;i<=N;i++){
		arr[i].resize(M+1);
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			cin>>arr[i][j];
		}
	}
	for(int i=0;i<K;i++){
		int r=3,c=4,s=2;
		cin>>r>>c>>s;
		mv.push_back(rcs(r,c,s));
	}
	vector<bool> temp(K);
	getMinVal(arr,temp,0);
	cout<<ans;
}
void getMinVal(vector<vector<int>> arr,vector<bool> com,int cnt){
	int ret=getVal(arr);
	if(cnt==K) ans=min(ans,ret);
	for(int i=0;i<com.size();i++){
		if(com[i]==false){
			com[i]=true;
			vector<vector<int>> temparr=arr;
			doSpin(temparr,mv[i].r,mv[i].c,mv[i].s);
			getMinVal(temparr,com,cnt+1);
			com[i]=false;
		}
	}
}