#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
#define ALPHABETS 26
const char base='a';
class Trie
{
	public:
	int num_child=0;
	bool is_root=false;
	bool is_terminal=false;
	Trie* child[ALPHABETS]={}; 
	void insert(const char* key);
	Trie* find(const char* key);
	~Trie() ///////////////////////필수!!!!!!!!!!!!!!!!!!
    {
        for (int i = 0; i < 26; i++)
            if (child[i])
                delete child[i];
    }
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
		{
			num_child++;
			this->child[index]=new Trie();
		}
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
vector<int> ans;
void dfs_Trie(Trie* trie,int cnt)
{
	if(!trie->is_root)
	{
		if(trie->is_terminal)
			ans.push_back(cnt);
		if(!(trie->num_child==1&&!trie->is_terminal))
	 	cnt++;
	}
	else
		cnt++;
	for(int i=0;i<ALPHABETS;i++)
	{
		if(trie->child[i])
			dfs_Trie(trie->child[i],cnt);
	}
}
int main()
{
	while(1)
	{
		ans=vector<int>();
		int N;
		cin>>N;
		Trie* trie=new Trie();
		if(cin.eof()==true)
				break;
		int temp=N;
		while(temp--)
		{
			char buffer[81];
			cin>>buffer;
			trie->insert(buffer);
		}
		trie->is_root=true;
		dfs_Trie(trie,0);
		int s_ize=ans.size();
		double total=0;
		for(int i=0;i<ans.size();i++)
		{
			total+=ans[i];
		}
		cout<<fixed<<setprecision(2)<<floor(total*100/s_ize+0.5)/100<<'\n';
		delete trie;
	}
}