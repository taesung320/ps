#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef int ll;
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
	return 	tree[node]=diff;
	}
	else{
		int mid=(left+right)/2;
		ll leftResult=updateTree(tree,arr,node*2,left,mid,trgt,diff);
		ll rightResult=updateTree(tree,arr,node*2+1,mid+1,right,trgt,diff);
		return tree[node]=cal(leftResult,rightResult);
	}
}
//[0,i-1]구간에 A[i]보다 크거나 작은 수의 개수를 구하는 문제
//나중에 펜윅트리 공부 ㄱㄱㄱ 해야되나..

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin>>N;
	tree.resize(4*N);
	arr.resize(N+1);
	priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>>> cow; // 키순으로 인덱스 부여한다
	for(int i=1;i<arr.size();i++){
		int x;
		cin>>x;
		cow.push({x,i});
	}
	while(!cow.empty()){
		pair<int,int> curcow=cow.top();
		cow.pop();
		arr[curcow.second]=cow.size()+1;
	}
	//이러면 범위를 줄일ㅇ수잇음
	vector<ll> reverseTree=tree;
	vector<ll> reverseArr=arr;
	reverse(reverseTree.begin(),reverseTree.end());
	reverse(reverseArr.begin(),reverseArr.end());
	int leftSide[100001]={};// i 번째 왼쪽에 있는 큰 수의 개수
	int rightSide[100001]={};
	for(int i=1;i<arr.size();i++){
		int left_no=0;
		int right_no=0;
		if(i!=1){
			left_no=getRangeResult(tree,arr,1,1,N,min(N,arr[i]+1),N);
			right_no=getRangeResult(reverseTree,reverseArr,1,1,N,min(N,reverseArr[i-1]+1),N);	
		}
		updateTree(tree,arr,1,1,N,arr[i],1);
		updateTree(reverseTree,reverseArr,1,1,N,reverseArr[i-1],1);
		leftSide[arr[i]]=left_no;//왼쪾에 arr[i]보다 큰 개스
		rightSide[reverseArr[i-1]]=right_no;///////////////////////////////////N+1 size일때 뒤집으면 [0]이 맨뒤로간다는것
		//cout<<arr[i]<<" l::"<<left_no<<" // "<<reverseArr[i-1]<<" r::"<<right_no<<endl;
	}
	int cnt=0;
	for(int i=1;i<arr.size();i++){
		int l=leftSide[arr[i]];
		int r=rightSide[arr[i]];
		if(max(l,r)>2*min(l,r)){
			cnt++;
		}
		//cout<<arr[i]<<" l::"<<l<<" r::"<<r<<endl;
	}
	cout<<cnt;
}
