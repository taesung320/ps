//
//  14891.cpp
//  boj
//
//  Created by 윤태성 on 2021/11/17.
//
#include <iostream>
#include <string>
using namespace std;
const bool RIGHT=true;
const bool LEFT=false;
const int CLOCK=1;
const int idx[]={1,2,3,4};
const int offset[]={0,1,2,4,8};
struct cycle{
    string cycleBit="";
    int coreIndex=0;
    cycle(string cyc="",int idx=0){
        cycleBit=cyc;
        coreIndex=idx;
    }
};
bool spined[5]={};
void initSpined(){
    for(int e:idx){
        spined[e]=false;
    }
}
cycle cycleArr[5]={};
char getRLbit(int k,bool RL){//t/f : r/l
    int curIndex=cycleArr[k].coreIndex;
    if(RL==LEFT){//'9
        curIndex=(curIndex+6)%8;
    }else if(RL==RIGHT){//'3
        curIndex=(curIndex+2)%8;
    }
    return cycleArr[k].cycleBit[curIndex];
}
void spinCycle(int k,int dir){//1/-1 : c/uc
    int temp=cycleArr[k].coreIndex;
    temp=(dir==CLOCK?(temp+7)%8:(temp+1)%8);
    cycleArr[k].coreIndex=temp;
}
void spinWholeCycle(int k,int d){
    spined[k]=true;
    if(k!=1&&!spined[k-1]&&(getRLbit(k-1, RIGHT)!=getRLbit(k, LEFT))){
        spinWholeCycle(k-1,d*-1);
    }
    if(k!=4&&!spined[k+1]&&(getRLbit(k+1, LEFT)!=getRLbit(k, RIGHT))){
        spinWholeCycle(k+1,d*-1);
    }
    spinCycle(k, d);
}
int main(){
    for(int e:idx){
        cin>>cycleArr[e].cycleBit;
    }
    int N=0;
    cin>>N;
    for(int i=0;i<N;i++){
        int cycIdx,spinDir;
        cin>>cycIdx>>spinDir;
        initSpined();
        spinWholeCycle(cycIdx,spinDir);
    }
    int ans=0;
    for(int e:idx){
        int core=cycleArr[e].coreIndex;
        ans+=(cycleArr[e].cycleBit[core]=='1'?offset[e]:0);
    }
    cout<<ans;
}


