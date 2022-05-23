#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
const int INF=1e9;
int N,P;
//cache 형식
int cache[1<<16]={};//[다음조합에서] P개로 만드는 최소비용?
int cost[16][16]={};

int DP(int com,int p){
	
	if(p>=P)
		return 0;
	int& ret=cache[com];
	if(ret!=-1) return ret;
	ret=INF;
	for(int i=0;i<N;i++){
		if(com&(1<<i)){//i번째가 정상임
			for(int j=0;j<N;j++)//
			{
				if(!((com&(1<<j))))//j번째가 고장이고 i로 j를고칠수있다.
				{
					ret=min(ret,cost[i][j]+DP(com+(1<<j),p+1));
				}
			}
		}
	}//p라면 진작 나갔을꺼고 p-1에서 못고치면 INF 나옴
	//cout<<com<<" "<<p<<" return::"<<ret<<endl;
	return ret;
}
int main()
{
	cin>>N;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			cin>>cost[i][j];
	string s;
	cin>>s;
	cin>>P;
	int curp=0;
	int startCom=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='Y'){
			startCom+=(1<<i);
			curp++;
		}
	}
	memset(cache,-1,sizeof(cache));
	int ans=DP(startCom,curp);
	cout<<(ans>=INF?-1:ans);
}