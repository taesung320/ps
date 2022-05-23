#include<iostream>
using namespace std;
#include<string>
string zero[]={"","0","00","000","0000"};
string findZero(string s){
	string temp="";
	string ret="";
	for(int i=0;i<s.size();i++){
		if(s[i]==':'){
			if(temp.size()!=0||i==0){
				string four_bit=zero[4-temp.size()]+temp;
				ret+=(four_bit+":");
				temp="";
			}else{
				ret+=":";
			}
		}else{
			temp.push_back(s[i]);
		}
	}
	string four_bit=zero[4-temp.size()]+temp;
	ret+=(four_bit);
	return ret;
}
string zeroRange(int n){
	string ret="0000";
	while(--n){
		ret+=":0000";
	}
	return ret;
}
string findRange(string s){
	for(int i=0;i<s.size()-1;i++){
		if(s.substr(i,2)=="::"){
			int n;
			if(s.size()<39){
				n=(39-s.size()+1)/5;
				return (s.substr(0,i+1)+zeroRange(n)+s.substr(i+1,s.size()-i-1));
			}else{
				s.erase(s.begin()+i);
				return s;
			}
			
		}
	}
	return s;
}
int main(){
	string inpt;
	cin>>inpt;
	cout<<findRange(findZero(inpt));
}