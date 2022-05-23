#include<iostream>
#include<string>
#include<utility>
using namespace std;

typedef pair<int,int> Record;//네 부분으로 나눠지는 화면, 상좌 상우 하좌 하우 , 문자열에서 각각을 나타내는 구간을 나타낸다

int solve(string& input,int start);
void changeStr(int start,int end,string& str,string newStr);

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;
	while(T--)
	{
		string input;
		cin>>input;
		if(input.size()==1)
		{
			cout<<input<<'\n';
			continue;
		}
		solve(input,0);
		cout<<input<<'\n';
	}
}

int solve(string& input,int start)
{
	Record record[4]={};
	int cur=start+1;
	for(int i=0;i<4;i++)
	{
		if(input[cur]!='x')
		{
			record[i]={cur,cur};
			cur++;
		}
		else//input[cur]==x
		{
			int temp=cur;
			cur=solve(input,cur);//solve-> 이 부분화면이 어디서 끝나는지
			record[i]={temp,cur};
			cur++;
		}
	}
	//구간이 정해지면 구간끼리 바꾼다 (1,2,3,4)-->(3,4,1,2)
	string tempStr;
	int upDownFilp[4]={2,3,0,1};
	for(int i=0;i<4;i++)
	{
		Record temp=record[upDownFilp[i]];
		tempStr+=input.substr(temp.first,temp.second-temp.first+1);
	}
	changeStr(start+1,cur-1,input,tempStr);
	return record[3].second;
}

void changeStr(int start,int end,string& str,string newStr)
{
	int i=start,j=0;
	while(i<=end&&j<newStr.size())
	{
		str[i]=newStr[j];
		i++;j++;
	}
}