#include<iostream>
#include<string>
#include<vector>
using namespace std;
void printWWWWW(unsigned int t){
	int msk=(1<<8)-1;
	for(int i=3;i>=1;i--){
		unsigned int temp=(t&(msk<<(i*8)));
		cout<<(temp>>(i*8))<<".";
	}
	cout<<(t&msk)<<endl;
}
int main(){
	unsigned int n;
	cin>>n;
	vector<unsigned int> arr(n);
	for(unsigned int i=0;i<n;i++){
		string s;
		cin>>s;
		string temp="";
		unsigned int cur=0;
		unsigned int ofs=32;
		for(unsigned int j=0;j<s.size();j++){
			if(s[j]=='.'){
				ofs-=8;
				cur|=(stoi(temp)<<(ofs));
				temp="";
			}else{
				temp.push_back(s[j]);
			}
		}
		cur|=stoi(temp);
		arr[i]=cur;
	}
	unsigned int netAdress=arr[0];
	unsigned int subnetmask=arr[0];
	for(unsigned int i=1;i<n;i++){
		netAdress&=arr[i];
		subnetmask|=arr[i];
	}
	subnetmask^=netAdress;
	printWWWWW(netAdress);
	printWWWWW(~subnetmask);
	
}