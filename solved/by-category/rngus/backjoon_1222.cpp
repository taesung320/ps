
#include<iostream>
using namespace std;
const int rMax=1415;
const int aMax=2000001;
int ansCnt[aMax]={};
int student[200000]={};
//20200408
//공통된 약수 * 공통된 약수를 가지는 학교의 개수
//약수 찾을땐 최댓값의 1/2제곱만 곱하면됨 --> 200만이니까 루트 씌우면 1415못 넘는다 
//이만큼 돌리고 최댓값 학생수를 뽑아내서 2 ~i~1415

int main()
{

	int N=0;
	int maxStdt=0;
	cin>>N;
	for(int i=0;i<N;i++)
	{
		cin>>student[i];
	}
	
	for(int i=1;i<rMax;i++)
	{

		for(int j=0;j<N;j++)
		{
			if(student[j]%i==0)
			{
				ansCnt[i]+=i;
				int temp=student[j]/i;
				if(temp>=rMax)
				{
					ansCnt[temp]+=temp;
				}
			}
		}		
	}	
	int ans=0;
	for(int i=1;i<aMax;i++)
	{
		if(ansCnt[i]>i&&ans<ansCnt[i])
			ans=ansCnt[i];
	}
	cout<<ans;
	
	
}
