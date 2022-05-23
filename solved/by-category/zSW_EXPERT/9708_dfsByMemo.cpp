#include<iostream>
using namespace std;
#include<algorithm>
#include<cstring>
int N;
int ans;
int max_el;
int arr[100000]={};
int cnt_of[1000001]={};
void clearArr(){
	memset(arr,0,N);
	memset(cnt_of,0,sizeof(cnt_of));
	ans=N=max_el=0;
}
int solve(int n)
{
	if(cnt_of[n]>0)
		return cnt_of[n];
	cnt_of[n]=1;
	int temp=n*2;
	int M=0;
	while(temp<=max_el){
		if(cnt_of[temp])
			M=max(M,solve(temp));
		temp+=n;
	}
	cnt_of[n]+=M;
	return cnt_of[n];
}

int main()
{
	int T;
	cin>>T;
	int temp=T;
	while(T--){
		clearArr();
		cin>>N;
		for(int i=0;i<N;i++){
			cin>>arr[i];
			cnt_of[arr[i]]--;
			max_el=max(arr[i],max_el);
		}//굳이 입력받은 배열을 정렬할 필요가 없다....왜인지는 
		//재귀-확신이 있어야함 정확히 짜놓고 이럴것이다. 딲 잡고 과감해져야함 이것만 정확하면 다른건 문제없다는 마인드
		//자기자신을 증명 -> 확신
		//LIS는 여젼히 ... 피하고있는 내자신 .... 2020.07.20
		for(int i=0;i<N;i++){
			ans=max(ans,solve(arr[i]));//n으로 시작하는 수열의 최대길이
		}
		cout<<"#"<<(temp-T)<<" "<<ans<<'\n';
	}
}