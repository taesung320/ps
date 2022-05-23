#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>

using namespace std;
typedef long long int ui;
pair<int,ui> prob[200001]={};
priority_queue<ui,vector<ui>> pq;
int main()
{
	int N;
	cin>>N;
	prob[0]={-1,0};
	for(int i=1;i<=N;i++)
		cin>>prob[i].first>>prob[i].second;
	sort(prob,prob+N+1);
	ui day=N,ans=0;
	for(int i=N;i>=0;){
		if(prob[i].first==day){
			pq.push(prob[i].second);
			i--;
		}
		else{
			day--;
			if(!pq.empty()){
				ans+=pq.top();
				pq.pop();
			}
			if(day==0)
				break;
		}
	}
	cout<<ans;
}