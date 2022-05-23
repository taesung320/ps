//너무 복잡한 생각에 비해 떨어지는 구현력....
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<utility>
using namespace std;
typedef pair<int,int> ed;
const int INF=1e8;
int N;
int mN;
int sumCache[(1<<16)]={};
vector<ed> v[(1<<16)]={};
int edge[17][17]={};

int DP(int com,int n){
	//cout<<com<<"--\n";
	if(n==1) return 0;
	int& ret=sumCache[com];
	if(ret!=-1){
		//cout<<com<<" ::: "<<ret<<endl;
		return ret;
	} 
	//기저, com 의 원소가 2개일때
	if(n==2){
		int lr[2]={};
		int j=0;
		for(int i=0;i<N;i++){
			if(com&(1<<i)){
				lr[j++]=i+1;
			}
		}
		//2인데 한쪽이 INF인 경우*******************예외있음
		//if(edge[lr[0]][lr[1]]!=INF&&edge[lr[1]][lr[0]]!=INF){
			v[com].push_back({lr[0],lr[1]});
			v[com].push_back({lr[1],lr[0]});
		//}
		ret=edge[lr[0]][lr[1]]+edge[lr[1]][lr[0]];
		//cout<<com<<" ::: "<<ret<<endl;
		return ret;
	}
	ret=INF*16;
	//com 에서 원소를 하나 씩 뺀
	for(int i=1;i<=N;i++){
		if(com&(1<<(i-1)))
		{//결과들중 1개 -->dp(com-(1<<i))
		//와 결합한것들
		int tempSum=DP(com-(1<<(i-1)),n-1); // 이게 끝나면 v결정되있음
		vector<ed> tempV=v[com-(1<<(i-1))];
		//결정된 v에 추가할때의 최소를 구한다.
		int trgt=0;//즉 , 교체할 간선을 구한다.
		if(tempV.empty()) continue;
		int mVal=edge[tempV[0].first][i]+edge[i][tempV[0].second]-edge[tempV[0].first][tempV[0].second];
		for(int x=1;x<tempV.size();x++){
			int curS=tempV[x].first;
			int curE=tempV[x].second;
			int curV=edge[curS][i]+edge[i][curE]-edge[curS][curE];
			if(mVal>curV){
				trgt=x;
				mVal=curV;
			}
		}
		//최소값 갱신 및 v[com] 결정한다.
		if(ret>mVal+tempSum||i==1){
			tempV.push_back({tempV[trgt].first,i});
			tempV.push_back({i,tempV[trgt].second});
			tempV.erase(tempV.begin()+trgt);
			ret=tempSum+mVal;
			v[com]=tempV;
			//cout<<"in "<<com<<" "<<i<<") + "<<(com-(1<<i))<<" ("<<tempV[trgt].first<<","<<tempV[trgt].second<<") "<<mVal<<endl;
		}
		}
	}
	//cout<<com<<" ::: "<<ret<<endl;
	return ret;
}
int main()
{
	memset(sumCache,-1,sizeof(sumCache));
	cin>>N;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
		{
			int x;
			cin>>x;
			edge[i][j]=(x?x:INF);
		}
			
	int ans=DP((1<<N)-1,N);
	cout<<ans;
}