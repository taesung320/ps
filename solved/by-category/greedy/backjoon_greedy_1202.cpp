#include<iostream>
#include<algorithm>
#include<utility>
#include<queue>
using namespace std;//뭐부터 봐야하는지 파악, 한정보에 대해 정렬후 한번씩만 보는 방법 생각
pair<int,int> jj[300000]={};
int wb[300000]={};
int N,K;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin>>N>>K;
	for(int i=0;i<N;i++)
		cin>>jj[i].first>>jj[i].second;
	for(int i=0;i<K;i++)
		cin>>wb[i];
	sort(wb,wb+K);
	sort(jj,jj+N);
	int i=0,j=0;
	long long int ans=0;
	priority_queue<int,vector<int>> pq;
	for(int i=0;i<K;i++)
	{
		while(j<N&&jj[j].first<=wb[i])
		{
			pq.push(jj[j++].second);			
		}
		if(!pq.empty())
		{
			ans+=pq.top();
			pq.pop();
		}
	}
	cout<<ans<<'\n';
}