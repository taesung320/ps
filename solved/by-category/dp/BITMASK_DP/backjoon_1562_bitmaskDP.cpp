#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int N;
int cache[100][10][1<<11]={};//[len][end][com] len 길이에서 end로 끝나고 com조합이 정해질때 조건을 만족하게 되는 경우의수
const int modNum=1000000000;
int DP(int len,int end,int com){
	if(len==N){
		if(com==((1<<10)-1))
			return 1;
		return 0;
	}
	int& ret=cache[len][end][com];
	if(ret!=-1) return ret;
	ret=0;
	{
		if(end!=9){
			int nextCom=com;
			if(!(nextCom&(1<<(end+1)))){
				nextCom+=(1<<(end+1));
			}
			ret+=DP(len+1,end+1,nextCom);
			ret%=modNum;
		}
		if(end!=0){
			int nextCom=com;
			if(!(nextCom&(1<<(end-1)))){
				nextCom+=(1<<(end-1));
			}
			ret+=DP(len+1,end-1,nextCom);
			ret%=modNum;
		}
	}
	return ret%modNum;
	
}
int ans(){
	int ret=0;
	for(int i=1;i<10;i++){
		ret+=DP(1,i,1<<i);
		ret%=modNum;
	}
		
	
	return ret;
}
int main()
{
	memset(cache,-1,sizeof(cache));
	cin>>N;
	cout<<ans();
}
