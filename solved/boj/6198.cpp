//
//  6198.cpp
//  boj
//
//  Created by 윤태성 on 2021/11/15.
//

#include<iostream>
#include<stack>
//#include<algorithm>
using namespace std;
stack<pair<long long int,long long int>> stk;//first:
int main(){
    int N=0;
    int arr[80001]={};
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
   long long int ans=0;
    for(int i=N-1;i>=0;i--){
        if(i==N-1){
            stk.push({arr[i],0});
        }else{
            long long int result=0;
            {
                while(!(stk.empty())&&arr[i]>stk.top().first){
                    result+=(stk.top().second+1);
                    stk.pop();
                }
                stk.push({arr[i],result});
                ans+=result;
            }
        }
    }
    cout<<ans;
}
