#include<iostream>
#include<algorithm>
#include<vector>
//포인터들의 시작위치랑 이동 방향... 정해지면 계속 같은 방향으로 간다.
//배열 단순 비교보단 이분탐색 가능한지
//구간을 움직이면서 대상을 찾을지
//대상 고정해놓고 구간을 움직일지
using namespace std;
typedef long long int ll;
int main(){
	int N;
	cin>>N;
	vector<ll> arr(N);
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	sort(arr.begin(),arr.end());
	vector<bool> check(N);
	int ans=0;
	for(int i=0;i<arr.size();i++){
		int cur=arr[i];
		int s=0;
		int e=N-1;
		while(s<e){
			int temp=arr[s]+arr[e];
			if(cur>temp){
				s++;
			}else if(cur<temp){
				e--;
			}else if(cur==temp){
				if(!(s==i||e==i)){
					ans++;
					break;
				}else if(s==i){
					s++;
				}else if(e==i){
					e--;
				}
				
			}
		}
	}
	cout<<ans;
}