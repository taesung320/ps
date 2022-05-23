#include<iostream>
#include<cstdio>
using namespace std;
#define ALPHABETS 26
const char base='a';
class Trie
{
	public:
	bool is_terminal=false;
	Trie* child[ALPHABETS]={}; //단어의 끝임을 표시하는 변수입니다.
	void insert(const char* key); //새로운 문자열을 트라이에 추가하는 코드입니다.
	Trie* find(const char* key); // key에 해당하는 문자열을 접두어로 가지고 있는지 확인하고 가지고 있다면 해당 접두어가 끝나는 부분의 위치를 반환합니다.
	bool string_exist(const char* key); //key에 해당하는 문자열이 포함되어 있는지 확인하는 코드입니다. 해당 key의 문자열이 있다면 true를 반환하고 없으면 false를 반환합니다.
};
void Trie::insert(const char* key)
 {
	 if(*key=='\0')
	 {
		 this->is_terminal=true;
	 }
	else
	{
		int index=*key-base;
		if(this->child[index]==0)
			this->child[index]=new Trie();
		this->child[index]->insert(key+1);
		
	}
 }
Trie* Trie::find(const char* key)
{
	int index=*key-base;
	if(*key=='\0')
		return this;
	if(this->child[index]==0)
		return NULL;
	else
		return this->child[index]->find(key+1);
}
bool Trie::string_exist(const char* key)
{
	if(*key=='\0'&&this->is_terminal)
		return true;
	int index=*key-base;
	if(this->child[index]==0)
		return false;
	return this->child[index]->string_exist(key+1);
}


int main()
{
	Trie* trie=new Trie();
	char inpt[501];
	int N,M;
	cin>>N>>M;
	for(int i=0;i<N;i++)
	{
		scanf("%s", inpt);
		trie->insert(inpt);
	}
	int ans=0;
	for(int i=0;i<M;i++)
	{
		scanf("%s", inpt);
		if(trie->string_exist(inpt))
			ans++;
	}
	cout<<ans;
}