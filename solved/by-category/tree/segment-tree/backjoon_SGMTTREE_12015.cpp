#include<iostream>
using namespace std;
typedef long long int ll;
const int N=1<<20;
int tree[4*N]={};
int arr[N]={};
ll cal(ll a,ll b){
	return a+b;
}
ll makeTree(int node,int start,int end)//node: 현재 노드 , start~end : 채워야하는 범위
{
	if(start==end) return tree[node]=arr[start];
	int mid=(start+end)/2;
	ll leftResult=makeTree(node*2,start,mid);
	ll rightResult=makeTree(node*2+1,mid+1,end);
	return cal(leftResult,rightResult);
}
//node위치에서 left~right에 속하는 구간들을 전부 더한다...
ll getRangeSum(int node,int start,int end,int left,int right){
	if(left>end||right<start)// 공통부분이 없다
		return 0;
	if(left<=start&&end<=right)//다음 구간이[start,end]  [left,right] 에 속하는 경우
		return tree[node];
	//위에 조건에 해당하지 않는경우 반반 나눠서 파악한다.
	int mid=(start+end)/2;
	ll leftResult=getRangeSum(node*2,start,mid,left,right);
	ll rightResult=getRangeSum(node*2+1,mid+1,end,left,right);
	return cal(leftResult,rightResult);
}
void updateTree(int node,int left,int right,int trgt,int diff){//합기준 값이 변할때
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
