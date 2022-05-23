#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<stack>
#include<queue>
using namespace std;
typedef long long int hanoi;
typedef pair<hanoi,int> hq;
map<hanoi,int> m; 
queue<hq> q;
bool isMono(hanoi h);
int bfs();
char alp[4]={'-','A','B','C'};
hanoi char2i(char c){
	if(c=='A') return 1;
	if(c=='B') return 2;
	if(c=='C') return 3;
}
hanoi getStick(hanoi h,int i){
	hanoi temp=1<<(20*(i+1));
	temp--;
	hanoi ret=h&temp;
	ret=(ret>>(20*i));
	return ret;
}
void addDisk(hanoi& h,int i,char disk){
	hanoi stick=getStick(h,i);
	hanoi x=3;
	int cnt=0;
	while(stick&x){
		x=(x<<2);
		cnt++;
	}
	hanoi t=char2i(disk);
	t=(t<<(2*cnt));
	stick=(stick|t);
}
void popDisk(hanoi& h,int i){
	hanoi x=3;
	int cnt=0;
	while(stick&x){
		x=(x<<2);
		cnt++;
	}
	hanoi t=1;
	t=(t<<(2*cnt));
	t--;
	stick=(stick&t);
}
char getTopOnStick(hanoi h,int i){
	hanoi stick=getStick(h,i);
	hanoi x=3;
	hanoi t=0;
	while(stick&x){
		t=stick&x;
		stick=(stick>>2);
	}
	return alp[t];
}
bool isEmpty(hanoi h,int i){
	return !getStick(h,i);
}

int main(){
	hanoi start=0;
	for(int i=0;i<3;i++){
		int a;
		string s;
		cin>>a>>s;
		for(int j=0;j<s.size();j++){
			addDisk(start,i,s[j]);
			cout<<"stick::"<<i<<" "<<getStick(start,i)<<endl;
		}
	}
	q.push({start,0});
	m.insert({start,0});
	int ans=bfs();
	cout<<ans;
}
int bfs(){
	while(!q.empty()){
		hanoi cur=q.front().first;
		int curN=q.front().second;
		q.pop();
		if(isMono(cur)) return curN;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(i==j) continue;
				hanoi next=cur;
				int nextN=curN+1;
				//i 에서 j 로
				if(isEmpty(next,i)) continue;
				char ichar=getTopOnStick(next,i);
				istk.pop();
				jstk.push(ichar);
				//
				if(m.find(next)==m.end()){
					m.insert({next,0});
					q.push({next,nextN});
				}
			}
		}
	}
	return 0;
}
bool isMono(hanoi h){
	char t[3]={'A','B','C'};
	bool ret=true;
	for(int i=0;i<3;i++){
		while(!isEmpty(h,i)){
			if(getTopOnStick(next,i)!=t[i])
				return false;
		}
	}
	return ret;
}