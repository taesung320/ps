#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int arr[10000]={};
int main()//0이상을 0초과로 봐서 뻘짓오래했다
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,K;
	cin>>N>>K;
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	sort(arr,arr+N);
	int ans=arr[N-1]-arr[0];
	priority_queue<int,vector<int>> pq;
	for(int i=1;i<N;i++){
		pq.push(arr[i]-arr[i-1]);
	}
	while(--K&&!pq.empty()){
		ans-=pq.top();
		pq.pop();
	}
	cout<<ans;
}