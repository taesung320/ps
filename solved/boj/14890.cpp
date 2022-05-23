//
//  14890.cpp
//  boj
//
//  Created by 윤태성 on 2021/07/26.
//

#include <iostream>
#include <vector>
using namespace std;
int arr[100][100]={};
int N,L;
bool check(vector<int> v){
    vector<bool> hasL(N);
    int ret=true;
    for(int i=0;i<N-1;i++){
        if(v[i]==v[i+1]) continue;
        else{
            int offset=0;
            int curi=0;
            if(v[i]+1==v[i+1]){
                offset=-1;
                curi=i;
            }else if(v[i]==v[i+1]+1){
                offset=1;
                curi=i+1;
            }else{
                return false;//높이차 2이상
            }
            int tempL=L;
            if(hasL[curi]==true) return false;
            while(--tempL){
                if(curi+offset<0||curi+offset>=N) break;
                if(v[curi]==v[curi+offset]&&hasL[curi+offset]==false) {
                    curi+=offset;
                }
                else break;
            }
            if(tempL)return false;
            else{
                for(int k=0;k<L;k++){
                    hasL[curi-(k*offset)]=true;
                }
            }
        }
    }
    return ret;
}

int main(){
    cin>>N>>L;
    for(int i=0;i<N;i++){
        for (int j=0; j<N; j++) {
            cin>>arr[i][j];
        }
    }
    int ans=0;
    for(int i=0;i<N;i++){
        vector<int> v1;
        vector<int> v2;
        for(int j=0;j<N;j++){
            v1.push_back(arr[i][j]);
            v2.push_back(arr[j][i]);
        }
        if(check(v1)) ans++;
        if(check(v2)) ans++;
    }
    cout<<ans;
}
