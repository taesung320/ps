#include<iostream>
#include<cstring>
using namespace std;
int max3(int x,int y,int z){
	return max(x,max(y,z));
}
int min3(int x,int y,int z){
	return min(x,min(y,z));
}
int main(){
	int N;
	cin>>N;
	int maxA,maxB,maxC,minA,minB,minC;
	cin>>maxA>>maxB>>maxC;
	minA=maxA;minB=maxB;minC=maxC;
	for(int i=2;i<=N;i++){
		int a,b,c;
		cin>>a>>b>>c;
		int mxA,mxB,mxC,miA,miB,miC;
		mxA=a+max(maxA,maxB);
		mxB=b+max3(maxA,maxB,maxC);
		mxC=c+max(maxB,maxC);
		miA=a+min(minA,minB);
		miB=b+min3(minA,minB,minC);
		miC=c+min(minB,minC);
		maxA=mxA;maxB=mxB;maxC=mxC;
		minA=miA;minB=miB;minC=miC;
		cout<<"!!"<<maxA<<" "<<maxB<<" "<<maxC<<endl;
	}
	cout<<max3(maxA,maxB,maxC)<<" "<<min3(minA,minB,minC);

}