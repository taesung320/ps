//
//  17298.cpp
//  boj
//
//  Created by 윤태성 on 2021/11/15.
//

#include<iostream>
#include<stack>
using namespace std;

int main(){
    int N=0;
    int arr[1000000]={};
    int ans[1000000]={-1};
    stack<int> stk;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    stk.push(arr[N-1]);
    for(int i=N-1;i>=0;i--){
            while(!stk.empty()&&arr[i]>=stk.top()){
                stk.pop();
            }
            ans[i]=stk.empty()?-1:stk.top();
            stk.push(arr[i]);
    }
    for(int i=0;i<N;i++){
        cout<<ans[i]<<" ";
    }
}
