//
//  21611.cpp
//  boj
//
//  Created by 윤태성 on 2021/07/22.
//투포인터, 달팽이.. 구현 빨리하는 연습

#include <iostream>
#include <vector>
#include<utility>
using namespace std;
typedef pair<int,int> p;
int ans=0;
vector<vector<int>> arr;
int dx[]={0,-1,1,0,0};
int dy[]={0,0,0,-1,1};
int N,M;
int d[100]={};
int s[100]={};
vector<p> seq;
int getElem(int i){return arr[seq[i].first][seq[i].second];}
void setElem(int i,int v){
    arr[seq[i].first][seq[i].second]=v;
}
bool moveArr(){
    int idx=1;
    int cur=1;
    while(idx<(N*N)&&cur<(N*N)){
        if(getElem(cur)){
            idx++;
            cur++;
        }else{
            while(getElem(idx)==0){
                idx++;
                if(idx==N*N) break;
            }
            setElem(cur,getElem(idx));
            setElem(idx,0);
            idx++;
            cur++;
        }
    }
    return false;
    //return ret1&&ret2;
}
/*
 7 0
 48 47 46 45 44 43 42
 25 24 23 22 21 20 41
 26 9 8 7 6 19 40
 27 10 1 0 5 18 39
 28 11 2 3 4 17 38
 29 12 13 14 15 16 37
 30 31 32 33 34 35 36
 */
bool detectArr(){
    bool ret=false;
    int s=1;
    int e=1;
    int cnt=1;
    while(s<=e){
        if(getElem(e)==getElem(e+1)){
            if(getElem(e))
            cnt++;
            e++;
        }else{
            e++;
            if(cnt>=4){
                for(int k=s;k<e;k++){
                    ans+=getElem(k);
                    setElem(k,0);
                    ret=true;
                }
            }
            s=e;
            cnt=1;
        }
        if(e==N*N-1){
            if(cnt>=4){
                for(int k=s;k<e;k++){
                    ans+=getElem(k);
                    setElem(k,0);
                    ret=true;
                }
            }
            break;
        }
    }
    return ret;
}
vector<vector<int>> nextRound(){
    vector<vector<int>> ret(N);
    int idx=1;
    for(int i=0;i<N;i++)
        ret[i].resize(N);
    int s=1;
    int e=1;
    int cnt=1;
    while(s<=e){
        if(getElem(e)==getElem(e+1)){
            if(getElem(e))
             cnt++;
            e++;
        }else{
                //group (getElem(e),cnt)
            if(getElem(e)!=0){
               //cout<<e<<" "<<cnt<<" "<<getElem(e)<<endl;
                ret[seq[idx].first][seq[idx].second]=cnt;
                idx++;
                if(idx==(N*N)) break;
                
                ret[seq[idx].first][seq[idx].second]=getElem(e);
                idx++;
                if(idx==(N*N)) break;
            }
            e++;
            s=e;
            cnt=1;
        }
        if(e==N*N-1){
            if(getElem(e)!=0){
                ret[seq[idx].first][seq[idx].second]=cnt;
                idx++;
                if(idx==(N*N)) break;
                idx++;
                ret[seq[idx].first][seq[idx].second]=getElem(e);
                if(idx==(N*N)) break;
            }
            break;
        }
    }
    return ret;
}
void printArr(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
int main(){
    cin>>N>>M;
    arr.resize(N);
    for(int i=0;i<N;i++)
        arr[i].resize(N);
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<M;i++){
        cin>>d[i]>>s[i];
    }
    
    int i=(N-1)/2,j=(N-1)/2;
    seq.push_back({i,j});
    int cnt=1;
    int cur=1;
    int is=1;
    int js=-1;
    while(i||j){
        cur=cnt;
        while(cur--){
            j+=js;
            if(j<0)j=0;
            seq.push_back({i,j});
        }
        if(cnt==N) break;
        cur=cnt;
        while(cur--){
            i+=is;
            if(i<0)i=0;
            seq.push_back({i,j});
        }
        cnt++;
        js*=(-1);
        is*=(-1);
    }
    seq.pop_back();
    for(int i=0;i<M;i++){
        int di=d[i];
        int si=s[i];
        int x=(N-1)/2+dx[di],y=(N-1)/2+dy[di];
        while(si--){
            arr[x][y]=0;
            x+=dx[di];
            y+=dy[di];
        }
        moveArr();
        while(detectArr()){
            moveArr();
        }
       // printArr();
        arr=nextRound();
       // printArr();
    }
    cout<<ans;
}
