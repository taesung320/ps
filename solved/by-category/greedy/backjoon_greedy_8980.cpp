#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,int> pr;
typedef pair<pr,int> p;
p arr[10000]={};
bool cmp(p a,p b)
{
	if(a.first.second<b.first.second) return true;
	else if(a.first.second==b.first.second) return a.first.first<b.first.first;
	else return false;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N,CT,M;
	cin>>N>>CT>>M;
	for(int i=0;i<M;i++)
		cin>>arr[i].tf.first>>arr[i].tf.second>>arr[i].wgh;
	sort(arr,arr+M,cmp);
	
	cout<<ans;
}