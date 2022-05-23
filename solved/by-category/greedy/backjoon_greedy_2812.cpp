#include<iostream>
#include<string>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> info;
info a[500000]={};
int main(){
	int N,K;
	cin>>N>>K;
	string s,ans;
	cin>>s;
	for(int i=0;i<s.size();i++)
		a[i]=info{(s[i]-'0'),N-i};
	priority_queue<info,vector<info>> pq;
	int cnt=N-K;
	int curP=N;
	for(int i=0;i<=N;){
		if(N-i>=cnt){
			while(!pq.empty()&&(pq.top().first<a[i].first||pq.top().second>curP)) pq.pop();
			pq.push(a[i]);
			i++;
		}
		else{
			ans.push_back(char(pq.top().first+int('0')));
			curP=pq.top().second;
			pq.pop();
			cnt--;
		}
	}
	cout<<ans;
}