#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef unsigned long long int ull;
ull N,R,L;
const ull modNum=1000000007;
ull cache[101][101]={}; // [N][X]  N개 건물의 왼쪽에서 봤을때 보이는 건물 수 , 오른쪽은 그냥 반대로 함ㄴ되니까 상관없음 대신 맨처음엔 상관있음
ull com[101][101]={};
ull Ftable[101]={};
ull F(ull n){
    ull& ret=Ftable[n];
	if(n==0) return ret=1;
    if(ret!=-1) return ret;
	return ret=(n*(F(n-1)%modNum))%modNum;
}
ull addMod(ull X,ull Y){
	return (X%modNum+Y%modNum)%modNum;
}
ull comb(ull N,ull R){
	if(com[N][R]!=-1) return com[N][R];
	if(N==R||R<=0) return com[N][R]=com[N][N-R]=1;
	if(N<R) return 0;
	return com[N][R]=com[N][N-R]=addMod(comb(N-1,R-1),comb(N-1,R));
}
ull DP(ull N,ull X){// index 가 0이되는경우 , 경우의수 따질때 재대로 따지기 , 경우의수 특정 수의 나머지로 갈때 연산 일어날때마다 나머지 처리하기!
	ull& ret=cache[N][X];
	if(ret!=-1) return ret;
	if(X==N) return ret=1;
	if(X==1) return ret=F(N-1);
	ret=0;
	for(ull i=X;i<=N;i++)
	{
		if(i==0) continue;
		ret=addMod(ret,(((F(N-i)*comb(N-1,i-1))%modNum)*(DP(i-1,X-1)%modNum))%modNum);
	}
	return ret;
}
ull findAns(ull L,ull R){// index 가 음수가되거나 오버플로우 나는지 잘 확인하기
	ull ans=0;
	for(ull i=L;N>=i+R-1;i++){ 
		ull left=DP(i-1,L-1)%modNum;
		ull right=DP((N>=i?N-i:0),R-1)%modNum;
		//cout<<"i:: "<<i<<" L:: "<<i-1<<" X::"<<L-1<<"// R::"<<(N>=i?N-i:0)<<" X::"<<R-1<<endl;
		ull temp=(((left*right)%modNum)*comb(N-1,i-1))%modNum;
		ans=addMod(ans,temp);
	}
	return ans;
}
int main()
{
	memset(cache,-1,sizeof(cache));
	memset(com,-1,sizeof(com));
    memset(Ftable,-1,sizeof(Ftable));
	cin>>N>>L>>R;
	ull ans=findAns(min(R,L),max(R,L));
	cout<<ans;
}
