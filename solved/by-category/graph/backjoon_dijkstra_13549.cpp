#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int,int> node;
priority_queue<node,vector<node>,greater<node>> pq;
const int M=100001;
int cost[M]={};
int del[3]={-1,1,0};
void init_cost(){
	for(int i=0;i<M;i++)
		cost[i]=1e9;
}
void print_node(const node n)
{
	cout<<"(point::"<<n.second<<", cost::"<<n.first<<")";
}
void dkst(int N,int K){
	init_cost();
	pq.push({0,N});
	cost[N]=0;
	while(!pq.empty()){
		node top=pq.top();
		pq.pop();
		del[2]=top.second;
		int dstc=top.first;
		int cur=top.second;
		//cout<<"\nNOW::NODE ";print_node(top);
		for(int i=0;i<3;i++)
		{
			
			int next=cur+del[i];
			int next_val=dstc+(i==2?0:1);
			if(0<=next&&next<min(M,2*K-N)&&next_val<cost[next])
			{
				cost[next]=next_val;
				pq.push({next_val,next});
				//cout<<"\npush -> "<<next<<" , "<<next_val;
				
			}
		}
	}
}
///////////////////////////////////////////


int main()
{
	int N,K;
	cin>>N>>K;
	if(N==K) cout<<0;
	else if(N>K) cout<<N-K;
	else{
		dkst(N,K);
		cout<<cost[K];
	}
}