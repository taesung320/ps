#include<iostream>
using namespace std;
#include<cstring>
#include<cmath>
#include<iomanip>
#define ALPHABETS 128
const char base=0;
class Trie
{ 
	public:
	int num;
	bool is_terminal=false;
	Trie* child[ALPHABETS]={}; //단어의 끝임을 표시하는 변수입니다.
	void insert(const char* key); //새로운 문자열을 트라이에 추가하는 코드입니다.
	Trie* find(const char* key); // key에 해당하는 문자열을 접두어로 가지고 있는지 확인하고 가지고 있다면 해당 접두어가 끝나는 부분의 위치를 반환합니다.
	bool string_exist(const char* key); //key에 해당하는 문자열이 포함되어 있는지 확인하는 코드입니다. 해당 key의 문자열이 있다면 true를 반환하고 없으면 false를 반환합니다.
	int getNum(){return num;}
};
void Trie::insert(const char* key)
 {
	
	 if(*key=='\0')
	 {
		
		 this->is_terminal=true;
		 num=1;
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
	if(*key=='\0'&&is_terminal)
	{
		this->num++;
		return this;
	}
		
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
int cnt=0;
char str[31]={};
int char_index=0;
void dfs_by_trie(Trie* trie)
{
	if(trie->is_terminal)
		cout<<str<<" "<<fixed<<setprecision(4)<<floor((double(trie->getNum())*100/cnt)*10000+0.5)/10000<<"\n";
	for(int i=0;i<ALPHABETS;i++)
	{
		if(trie->child[i])
		{
			str[char_index++]=char(i+base);
			str[char_index]='\0';
			dfs_by_trie(trie->child[i]);
		}
	}
	if(char_index!=0)
	str[--char_index]='\0';
}

int main()
{
	Trie* trie=new Trie();
	char buffer[31]={};
	while (1) {
		cin.getline(buffer,31);
		if (cin.eof() == true) {
			break;
		}
		else
		{
			if(trie->find(buffer)==NULL)
				trie->insert(buffer);
			cnt++;
		}
	}
	dfs_by_trie(trie);
}