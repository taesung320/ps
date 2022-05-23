#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long int ll;
vector<ll> arr;
vector<ll> tree;
ll cal(ll a,ll b){
	return a+b;
}
ll getRangeResult(vector<ll>& tree,vector<ll>& arr,int node,int start,int end,int left,int right){
	if(left>end||right<start)
		return 0;
	if(left<=start&&end<=right)
		return tree[node];
	int mid=(start+end)/2;
	ll leftResult=getRangeResult(tree,arr,node*2,start,mid,left,right);
	ll rightResult=getRangeResult(tree,arr,node*2+1,mid+1,end,left,right);
	return cal(leftResult,rightResult);
}
ll updateTree(vector<ll>& tree,vector<ll>& arr,int node,int left,int right,int trgt,int diff){
	if(trgt<left||right<trgt)
	return tree[node];
	if(left==right){
	//arr[trgt]=diff;
	return 	tree[node]+=diff;
	}
	else{
		int mid=(left+right)/2;
		ll leftResult=updateTree(tree,arr,node*2,left,mid,trgt,diff);
		ll rightResult=updateTree(tree,arr,node*2+1,mid+1,right,trgt,diff);
		return tree[node]=cal(leftResult,rightResult);
	}
}
//값이랑 인덱스를을 매핑하고
//A랑 짝이되는 B의 위치를 기록한다
//A[i]=(i번째 기계가 B에서 등장하는 위치)
//ret+=(k in [0,N) [0,k-1]에서 k보다 큰 개수)
//큰 개수는 등장할때마다 1씩 추가해서 값을 인덱스로가지는 구간트리?만듥
int machineNumber_to_i[1000001]={};
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin>>N;
	tree.resize(4*N);
	arr.resize(N+1);
	
	for(int i=1;i<arr.size();i++){
		int x;
		cin>>x;
		machineNumber_to_i[x]=i;
	}
	for(int i=1;i<arr.size();i++){
		int x;
		cin>>x;
		arr[machineNumber_to_i[x]]=i;
	}//이렇게 하면 arr에 예제기준 { 3 , 1 , 4, 2 , 5 }로 저장됨
	
	ll ans=0;
	for(int i=1;i<arr.size();i++){
		ans+=getRangeResult(tree,arr,1,1,N,arr[i]+1,N);
		//cout<<i<<" "<<ans<<endl;
		updateTree(tree,arr,1,1,N,arr[i],1);
	}
	cout<<ans;

}
