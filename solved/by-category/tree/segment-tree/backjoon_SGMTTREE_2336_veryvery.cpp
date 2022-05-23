#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef int ll;
int N;
vector<ll> arr[3];
ll cal(ll a,ll b){
	return min(a,b);
}
ll getRangeResult(vector<ll>& tree,vector<ll>& arr,int node,int start,int end,int left,int right){
	if(left>end||right<start)
		return 1e9;
	if(left<=start&&end<=right)
		return (tree[node]?tree[node]:1e9);
	int mid=(start+end)/2;
	ll leftResult=getRangeResult(tree,arr,node*2,start,mid,left,right);
	ll rightResult=getRangeResult(tree,arr,node*2+1,mid+1,end,left,right);
	return cal(leftResult,rightResult);
}
ll updateTree(vector<ll>& tree,vector<ll>& arr,int node,int left,int right,int trgt,int diff){
	if(trgt<left||right<trgt)
	return (tree[node]?tree[node]:1e9);
	if(left==right){
	arr[trgt]=diff;
	return 	tree[node]=diff;
	}
	else{
		int mid=(left+right)/2;
		ll leftResult=updateTree(tree,arr,node*2,left,mid,trgt,diff);
		ll rightResult=updateTree(tree,arr,node*2+1,mid+1,right,trgt,diff);
		return tree[node]=cal(leftResult,rightResult);
	}
}
void amazingStudent(vector<bool>& check );
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N;
	for(int i=0;i<3;i++){
		arr[i].resize(N+1);
		for(int j=1;j<arr[i].size();j++){
			cin>>arr[i][j];
		}
	}
	vector<bool> checkAmazing(N+1);
	amazingStudent(checkAmazing);//모든 과목끼리 비교
	int ans=0;
	for(int i=0;i<checkAmazing.size();i++){
		if(checkAmazing[i]) ans++;
	}
	cout<<ans;
}
void amazingStudent(vector<bool>& checkAmazing){
	//두개 배열로 어메이징한 학생을 찾아내서 체크한다

	vector<ll> tree(4*N);
	vector<ll> a(N+1);
	vector<ll> vec(N+1);//[t2 등수]=t3 등수
	int no2t3rank[500001]={};
	int no2t2rank[500001]={};
	int best=1e9;
	for(int i=1;i<arr[1].size();i++){
		no2t2rank[arr[1][i]]=i;
	}
	for(int i=1;i<arr[2].size();i++){
		no2t3rank[arr[2][i]]=i;
	}
	for(int i=1;i<arr[2].size();i++){
		vec[no2t2rank[i]]=no2t3rank[i];
	}
	for(int i=1;i<arr[0].size();i++){
		int t2rank=no2t2rank[arr[0][i]];
		if(t2rank<best){//[no]=rank of no in arr[1]
			checkAmazing[arr[0][i]]=true;
			best=t2rank;
		}
		else{//arr[2] 에서 승부봐야함
			//t1에서도 i 보다 잘봤고 t2에서도 i보다 잘하는것들 중에서 가장 잘한것에게 먹히면
			//굉장해질수없다.
			int tt=getRangeResult(tree,a,1,1,N,1,t2rank-1);
			if(vec[t2rank]<tt)//이것도 아니면 또진거임
			{
				checkAmazing[arr[0][i]]=true;
			}
		}
		updateTree(tree,a,1,1,N,t2rank,vec[t2rank]);
	}
}
