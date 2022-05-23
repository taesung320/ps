#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<utility>
using namespace std;
priority_queue<int,vector<int>,greater<int>> pq;
bool visit[26]={};
bool hasCycle=false,mult=false;
int used[26]={};
int inde[26]={};
vector<int> eg[26]={};
string arr[100]={};
queue<int> ansQ;
int N,usedN=0;
void dfs()
{
	while(!pq.empty()&&ansQ.size()<usedN)
	{
		if(pq.size()>1)
			mult=true;
		int temp=pq.top();//indegree 0인거
		ansQ.push(temp);//temp--> checked
		pq.pop();
		for(int i=0;i<eg[temp].size();i++)//checked temp's nei 
		{
			int nxt=eg[temp][i];//nei
			inde[nxt]--;//visit-->degree-1
			if(inde[nxt]==0)//become zero -->pq push
				pq.push(nxt);
			
		}
	}
	if(ansQ.size()<usedN)
		hasCycle=true;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N;
	string s;
	for(int i=0;i<N;i++)
		cin>>arr[i];
	for(int i=0;i<N;i++){
		for(int j=0;j<arr[i].size();j++)
		{
			int num=arr[i][j]-'a';
			if(used[num]==0)
			{
				used[num]=1;
				usedN++;
			}
		}
	}
	for(int i=0;i<N-1;i++)
	{	
			string s1=arr[i];
			string s2=arr[i+1];
			int msz=(s1.size()<s2.size()?s1.size():s2.size());
			for(int k=0;k<msz;k++){
				if(s1[k]!=s2[k]){
					int a=int(s1[k]-'a');
					int b=int(s2[k]-'a');
					eg[a].push_back(b);
					inde[b]++;
					break;
				}
				else if(k==msz-1&&s1.size()>s2.size())
				{
					cout<<"!";
					return 0;
				}
			}
	}
	for(int i=0;i<26;i++)
		if(used[i]&&inde[i]==0)
			pq.push(i);
	dfs();
	if(hasCycle)
		cout<<"!";
	else if(mult)
		cout<<"?";
	else{
		while(!ansQ.empty()){
			if(used[ansQ.front()])
				cout<<char('a'+ansQ.front());
			ansQ.pop();
		}	
	}
}