#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long int ll;

ll cal(ll a,ll b){
	return a+b;
}
ll cal(ll a,ll b){
	return min(a,b);
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
		return (arr[0]<0?0:1e9);
	if(left<=start&&end<=right)
		return tree[node];
	int mid=(start+end)/2;
	ll leftResult=getRangeResult(tree,arr,node*2,start,mid,left,right);
	ll rightResult=getRangeResult(tree,arr,node*2+1,mid+1,end,left,right);
	return cal(leftResult,rightResult);
}
void updateTree(vector<ll>& tree,vector<ll>& arr,int node,int left,int right,int trgt,int diff){//합기준 값이 변할때
	if(trgt<left||right<trgt) return;
	tree[node]+=diff;
	if(left==right) {
		arr[left]+=diff;
	}
	else{
		int mid=(left+right)/2;
		updateTree(node*2,left,mid,trgt,diff);
		updateTree(node*2+1,mid+1,right,trgt,diff);
		return ;
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin>>N;
	tree.resize(4*N);
	arr.resize(N+1);
}
