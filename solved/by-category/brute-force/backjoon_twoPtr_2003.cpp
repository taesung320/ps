#include<iostream>
using namespace std;
int arr[10001]={};
int sum[10001]={};
int main(){
	int N,M;
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		cin>>arr[i];
	}
	int ans=0;
	sum[0]=arr[0];
	for(int i=1;i<=N;i++){
		sum[i]=arr[i]+sum[i-1];
	}
	int s=0;
	int e=1;
	while(true){
		if(sum[e]-sum[s]==M){
			ans++;
			if(s<N)
				s++;
			else
				break;
		}else if(sum[e]-sum[s]<M){
			if(e<N){
				e++;
			}else{
				break;
			}
		}else{
			if(s<N)
				s++;
			else
				break;
		}
	}
	cout<<ans;
	
}