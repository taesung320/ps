#include<iostream>
#include<queue>
#include<algorithm>
#include<string>
#include<map>
#include<utility>
using namespace std;
typedef pair<int,int> tl;
typedef pair<tl,int> pp;
map<string,int> mp;
int edge[500][500]={};
int s2i(string s){
	int ret=0;
	int d=1;
	for(int i=s.size()-1;i>=0;i--){
		ret+=(s[i]-'0')*d;
		d*=10;
	}
	//cout<<"s2i "<<ret<<endl;
	return ret;
}
string i2s(int i){
	string ret="";
	int d=1;
	while(d<=i){
		d*=10;
	}
	d/=10;
	while(d){
		ret.push_back((i/d)+'0');
		i%=d;
		d/=10;
	}
	//cout<<"i2s "<<ret<<endl;
	return (ret.size()==2?ret:"0"+ret);
}
int time2min(string s){
	//cout<<s<<endl;
	//cout<<s.substr(0,2)<<endl;
	int h=s2i(s.substr(0,2));
	int m=s2i(s.substr(3,4));
	return h*60+m;
}
string min2time(int m){
	string h=i2s(m/60);
	string mi=i2s(m%60);
	return h+":"+mi;
}
//map쓰고 번호 매칭해서 다익스트라 돌리고 정렬해서 ㄱ
priority_queue<pp,vector<pp>,greater<pp>> pq;
int N,M;
int main(){
	cin>>N>>M;
	for(int i=0;i<N;i++){
		string name,start,end;
		cin>>name>>start>>end;
		mp.insert({name,i});
		pq.push({{time2min(start),time2min(end)},i});
	}
	for(int i=0;i<M;i++){
		string from,to,tm;
		cin>>from>>to>>tm;
		cout<<mp[from]<<" "<<mp[to]<<endl;
		edge[mp[from]][mp[to]]=edge[mp[to]][mp[from]]=time2min(tm);
	}
	for(int i=0;i<N;i++){
		dk(i);//해서 다 구했다 치고
	}
	//q랑 막 해가지고 시간 구하면됨
}