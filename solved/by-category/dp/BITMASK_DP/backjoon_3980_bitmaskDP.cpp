#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;///답보고 알았음,,.,,..,,.,거의다 왔는데 결국 점화식,,, cache 형태 찾아야함
int avlt[11][11]={};//[번째선수][포지션에서 능력치]
int cache[11][1<<11]={};//[멤버까지 투입했을때][포지션의 조합] 의 최대 능력치
vector<int> pos_for[11];
const int N=11;

//2^22 *55 -> 시간초과임..
int DP(int member,int pos){
	if(member==11){
	if(pos==((1<<N)-1)) return 0;
		return -1e9;
	}
	int& ret=cache[member][pos];
	if(ret!=-1) return ret;
	ret=-1e9;
	for(int i=0;i<N;i++)
	{
		if(!(pos&(1<<i))&&avlt[member][i])
			ret=max(ret,avlt[member][i]+DP(member+1,pos+(1<<i)));
	}
	return ret;
}
int main()
{ 
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;
	while(T--){
		memset(cache,-1,sizeof(cache));
		memset(avlt,-1,sizeof(avlt));
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++){;
				cin>>avlt[i][j];
				if(avlt[i][j]) pos_for[i].push_back(j);
			}
		int ans=DP(0,0);
		cout<<ans<<"\n";
	}
}