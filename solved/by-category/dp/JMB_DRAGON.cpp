#include<iostream>
using namespace std;
#include<string>
typedef long long int ll;
string firstXYgen[2]={" FX-YFF"," FX+YFF"};//TRUE : + , FALSE : -
ll genLen[51]={2,5};
char getDragonByIndex(int N,ll L,int p,bool ty)
{
	/*cout<<"N:"<<N<<
		"\nL:"<<L<<
		"\np:"<<p<<endl;*/
	if(N<=1)
			return firstXYgen[ty][p];
	else{
		if(p<=L/2){
			return getDragonByIndex(N-1,L/2,p,1);
		}
		else if(p==L/2+1)
			return (ty?'+':'-');
		else {
			return getDragonByIndex(N-1,L/2,p-L/2-1,0);
		}
	}
}
long long int getLengthOfDragon(int N)
{
	for(int i=1;i<N;i++)
		genLen[i+1]=genLen[i]*2+1;
	return genLen[N];
}

int main()
{
	int c;
	cin>>c;
	
	while(c--)
	{
		int n,p,l;
		cin>>n>>p>>l;
		ll Ln=getLengthOfDragon(n);//max length
		string ans="";
		for(int i=p;i<p+l;i++)
		{
			ans.push_back(getDragonByIndex(n,Ln,i,1));
		}
		cout<<ans<<"\n";
	}
}