#include<iostream>
using namespace std;
#include<cstring>
#include<algorithm>
const int INF=-1*1e9;
int arr[1001]={INF};
int cache[1001]={};
int N;
int LIS(int start){
	int& ret=cache[start];
	if(ret!=-1) return ret;
	else{
		ret=1;
		for(int i=start+1;i<=N;i++){
			if(arr[start]<arr[i])
			ret=max(ret,LIS(i)+1);
		}
	}
	return ret;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>N;
	for(int i=1;i<=N;i++)
		cin>>arr[i];
	memset(cache, -1,sizeof(cache));
	int ans=LIS(0)-1;
	cout<<ans;
}