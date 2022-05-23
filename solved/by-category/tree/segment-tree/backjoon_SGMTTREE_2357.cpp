#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long int ll;
vector<ll> minTree;
vector<ll> maxTree;
vector<ll> arr;
vector<ll> arrI;
const int modN=1000000007;
ll m(ll a){
	return a%modN;
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
ll getRangeMin(vector<ll>& tree,vector<ll>& arr,int node,int start,int end,int left,int right){
	if(left>end||right<start)
		return (arr[0]<0?0:1e9);
	if(left<=start&&end<=right)
		return tree[node];
	int mid=(start+end)/2;
	ll leftResult=getRangeMin(tree,arr,node*2,start,mid,left,right);
	ll rightResult=getRangeMin(tree,arr,node*2+1,mid+1,end,left,right);
	return cal(leftResult,rightResult);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,K;
	cin>>N>>K;
	maxTree.resize(4*N);
	minTree.resize(4*N);
	arr.push_back(0);
	arrI.push_back(0);
	for(int i=1;i<=N;i++){
		int x;
		cin>>x;
		arr.push_back(x);
		arrI.push_back(-1*x);
	}
	makeTree(minTree,arr,1,1,N);
	makeTree(maxTree,arrI,1,1,N);
	int a,b,c;
	for(int i=0;i<K;i++)
	{
		int a,b;
		cin>>a>>b;
		cout<<getRangeMin(minTree,arr,1,1,N,a,b)
		<<" "<<-1*getRangeMin(maxTree,arr,1,1,N,a,b)<<"\n";
	}
}
