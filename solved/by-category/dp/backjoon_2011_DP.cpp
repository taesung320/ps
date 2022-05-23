#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	cin>>s;
	int ans[5010]={};
	ans[s.size()]=1;
	ans[s.size()-1]=1;
	for(int i=s.size()-1;i>=0;i--)
	{
		
		if(s[i]=='0'&&(i==0||!(s[i-1]=='1'||s[i-1]=='2')))
			
		{//0이 오면서 , 앞이 1,2가 아닌경우 --> 잘못된 암호
			cout<<0;
			return 0;
		}
		if(i==0)
			break;
		
		if(s[i-1]>='3')
		{//3 4 5 6 7 8 9 0 인경우
			ans[i-1]=ans[i]%1000000;
		}
		else if(s[i-1]!='0')			
		{//1 2 인경우
			if(s[i]<'7'||s[i-1]=='1')
			{ 	
				if(s[i]=='0')
					ans[i]=0;
				ans[i-1]=(ans[i]+ans[i+1])%1000000;
			}
				
			else
				
				ans[i-1]=ans[i]%1000000;
		}
		else
		{
				ans[i-1]=0;
		}
	}	
	cout<<ans[0];
}

