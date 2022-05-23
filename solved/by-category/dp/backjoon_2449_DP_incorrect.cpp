#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int rgt[201]={};
int cache[21][201][201]={};
int N,K;
int INF=1e9;
bool get_is_mono(int start,int end){
	for(int i=start;i<end;i++)
		if(rgt[i]!=rgt[i+1])
			return false;
	return true;
}
int DP(int color,int start,int end)
{
	int& ret=cache[color][start][end];
	if(ret!=-1) return ret;
	ret=INF; 
	if(get_is_mono(start,end)){
		return ret=(color==rgt[start]?0:1);
	} // [start,end]에 속한 전구가 한가지 색깔인가
	for(int i=1;i<=K;i++){
		int temp=INF;
		int n_start=start;
		int n_end=-1;
			for(int j=start;j<=end;j++){
				if(i==rgt[j]){
					if(n_end!=-1&&(color!=i||n_start!=start||n_end!=end)){
						if(temp!=INF)
							temp+=DP(i,n_start,n_end);
						else
							temp=DP(i,n_start,n_end);
						n_end=-1;
					}	
						n_start=j+1;
				}
				else{
				    n_end=j;
				}
			}
			if(n_end!=-1&&(color!=i||n_start!=start||n_end!=end)) {
				  if(temp!=INF)
						temp+=DP(i,n_start,n_end);
				  else
						temp=DP(i,n_start,n_end);
			}
			ret=min(ret,temp+(color==i?0:1));
	}
	return ret;
}
int main()
{
	memset(cache,-1,sizeof(cache));
	cin>>N>>K;
	for(int i=1;i<=N;i++)
		cin>>rgt[i];
	int ans=DP(0,1,N)-1;
	cout<<ans;
}