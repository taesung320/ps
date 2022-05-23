#include<iostream>
#include<queue>
#include<vector>
using namespace std;
priority_queue<int,vector<int>,greater<int>> pq;
vector<int> edg[32001]={};
int inde[32001]={};
bool isin[32001]={};
int N,M,a,b;//a->b 연결
queue<int> ansQ;
void topology_sort()//by_priorityQueue
{
	while(!pq.empty()&&ansQ.size()<N)
	{
		int temp=pq.top();//indegree 0인거
		ansQ.push(temp);//temp--> checked
		pq.pop();
		for(int i=0;i<edg[temp].size();i++)//checked temp's nei 
		{
			int nxt=edg[temp][i];//nei
			inde[nxt]--;//visit-->degree-1
			if(inde[nxt]==0)//become zero -->pq push
				pq.push(nxt);
			
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N>>M;
	for(int i=0;i<M;i++)
	{
		cin>>a>>b;
		edg[a].push_back(b);
		inde[b]++;
	}
	for(int i=1;i<=N;i++)
	{
		if(inde[i]==0)
		{	
			pq.push(i);	
		}
	}
	topology_sort();
	while(!ansQ.empty())
	{
		cout<<ansQ.front()<<" ";
		ansQ.pop();
	}
}