#include<iostream>
using namespace std;
int par[100001]={};
int arr[100000]={};
int find(int x)
{
	if(x==par[x])
		return x;
	else
		return par[x]=find(par[x]);// dp 같은느낌 경로 압축
}
void merge(int x,int y)
{
	int tx=find(x);
	int ty=find(y);
	if(tx==ty) return ;
	else par[ty]=tx;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int G,P,gi,cnt=0;
	cin>>G>>P;
	for(int i=1;i<=G;i++)
		par[i]=i;
	for(int i=0;i<P;i++)
		cin>>arr[i];
	for(int i=0;i<P;i++)
	{
		gi=arr[i];
		if(par[gi]==gi){
			cnt++;
			merge(gi-1,gi);	
		}
		else{
			int temp=find(gi);
			if(temp!=0){
				cnt++;
				merge(temp-1,temp);
			}
			else
				break;
		}
	}
	cout<<cnt;
}