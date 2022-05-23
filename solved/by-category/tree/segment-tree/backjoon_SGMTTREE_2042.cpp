#include<iostream>
#include<utility>
using namespace std;
typedef pair<pair<int,int>,long long int> node;
const int maxNode=(1<<23);
long long int arr[1000001]={};
node s_tree[maxNode]={};
bool isLeaf[maxNode]={};
int par(int N) {return N/2;}
int rc(int N) {return 2*N+1;}
int lc(int N) {return 2*N;}
long long int makeTree(int index,int start,int end) //segment tree 만드는 함수
{
	if(start==end)
	{
		s_tree[index]={{start,end},arr[start]};
		isLeaf[index]=true;
		return s_tree[index].second;
	}
		
	else{
		int mid=(start+end)/2;
		s_tree[index]={{start,end},makeTree(lc(index),start,mid)+makeTree(rc(index),mid+1,end)};
		return s_tree[index].second;
	}
}
int N,M,K;
int test(int num)
{
	if(s_tree[num].first.first!=s_tree[num].first.second)
	test(lc(num));
	if(s_tree[num].first.first!=s_tree[num].first.second)
	test(rc(num));
	cout<<"index::"<<num<<" start::"<<s_tree[num].first.first<<" end::"<<s_tree[num].first.second<<" sum::"<<s_tree[num].second<<endl;
	return 0;
}
//index 로 출발하는 완전탐색( 이진트리 )
long long int getSegSum(int index,int start,int end)
{

	pair<int,int> seg=s_tree[index].first;
	if(seg.first>end||seg.second<start) return 0;
	if(start<=seg.first&&seg.second<=end) return s_tree[index].second;
	else if(!isLeaf[index]){
		int nextL=lc(index);
		int nextR=rc(index);
		return getSegSum(nextL,start,end)+getSegSum(nextR,start,end);
	}
	else return 0;
}
void changeNode(int index,int target,long long int dff)
{
	pair<int,int> seg=s_tree[index].first;
	if(seg.first<=target&&target<=seg.second)
	{
		s_tree[index].second+=dff;
		if(!isLeaf[index]){
			changeNode(lc(index),target,dff);
			changeNode(rc(index),target,dff);
		}
	}
}
int main()
{

	cin>>N>>M>>K;
	for(int i=1;i<=N;i++)
		cin>>arr[i];
	makeTree(1,1,N);
	long long int a,b,c;
	for(int i=0;i<M+K;i++)
	{
		cin>>a>>b>>c;
		if(a==1)
		{
			long long int dff=c-arr[b];
			changeNode(1,b,dff);
		}
		else
		{
			long long int temp=getSegSum(1,b,c);
			cout<<temp<<'\n';
		}
	}
	
}