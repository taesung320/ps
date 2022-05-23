#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long int ll;
vector<ll> arr;
vector<ll> tree;
ll cal(ll a,ll b){
	return a+b;
}
ll makeTree(vector<ll>& tree,vector<ll>& arr,int node,int left,int right)//node: 현재 노드 , left~right : 채워야하는 범위
{
	if(left==right) return tree[node]=arr[left];
	int mid=(left+right)/2;
	ll leftResult=makeTree(tree,arr,node*2,left,mid);
	ll rightResult=makeTree(tree,arr,node*2+1,mid+1,right);
	return tree[node]=cal(leftResult,rightResult);
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
ll updateTree(vector<ll>& tree,vector<ll>& arr,int node,int left,int right,int trgt,int diff){//합기준 값이 변할때
	if(trgt<left||right<trgt)
	return tree[node];
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
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,Q;
	cin>>N>>Q;
	tree.resize(4*N);
	arr.resize(N+1);
	while(Q--){
		int t,p,q;
		cin>>t>>p>>q;
		if(t==1){
			updateTree(tree,arr,1,1,N,p,q);
		}
		if(t==0){
			ll ans=getRangeResult(tree,arr,1,1,N,p,q);
			cout<<ans<<"\n";
		}
	}
}
