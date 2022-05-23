#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int N,M;
int sheet[10][1<<10][1<<10]={};
int room[11]={};//1:벽 0:의자
const int iINF=-1*1e9;
void printb(int num) { 
	if (num == 0 || num == 1) { cout << num; return; } 
	printb(num/2); cout << num % 2; 
}
int getNextLineState(int idx,int comb,int sheetState){
	if(idx>=N-1) return 0;
	int ret=room[idx+1];
	for(int i=0;i<M;i++){
		if((comb&(1<<i))&&(sheetState&(1<<i))){
			if(i>0&&!(ret&(1<<(i-1)))){
				ret+=(1<<(i-1));
			}
			if(i<M-1&&!(ret&(1<<(i+1)))){
				ret+=(1<<(i+1));
			}
		}
	}
	return ret;
}
int DP(int idx,int comb,int sheetState)
{
	if(idx==N){
		return 0;	
	}
	int& ret=sheet[idx][comb][sheetState];
	if(ret!=-1) return ret;
	ret=iINF;
	int avobe=getNextLineState(idx,comb,sheetState);
	for(int j=0;j<M;j++){
		if(!(comb&(1<<j))){//공석이다
			int curLineState=comb+(1<<j);//앉았다고 표시한다
			int curSheetState=sheetState+(1<<j);
			if(j+1<M&&!(curLineState&(1<<(j+1)))){//우측 시야
				curLineState+=(1<<(j+1));
			}
			if(j-1>=0&&!(curLineState&(1<<(j-1)))){//좌측 시야
				curLineState+=(1<<(j-1));
			}
			ret=max(ret,1+DP(idx,curLineState,curSheetState));
		}
	}
		//이번줄에서 더이상 앉히지 않는경우
	ret=max(ret,DP(idx+1,avobe,0));
	//cout<<idx<<" line withComb ";printb(comb);
	//cout<<" return -->"<<ret<<"\n";
	return ret;

}

int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>N>>M;
		memset(sheet,-1,sizeof(sheet));
		memset(room,0,sizeof(room));
		for(int i=0;i<N;i++){
			string s;
			cin>>s;
			for(int j=0;j<s.size();j++){
				if(s[j]=='x')
				room[i]+=(1<<j);
			}
		}
		int ans=DP(0,room[0],0);
		cout<<ans<<"\n";
	}
}