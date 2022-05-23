//
// Created by 윤태성 on 2022/01/30.
//


#include<iostream>
#include<cmath>
#include<string>
#define INF 1000000000
using namespace std;
struct node{
    int parent=-1;
    string data;
    int left=-1;
    int right=-1;
    node(){};
    node(string _data,int lc,int rc):data(_data),left(lc),right(rc){};
} buff[1010];

void handleInput(int i,string data,int lc,int rc){
    //  cout<<"handle input "<<i<<" "<<data<<" "<<lc<<" "<<rc<<endl;
    buff[i] = node({data, lc, rc});
    if(lc!=-1)
        buff[lc].parent=i;
    if(rc!=-1)
        buff[rc].parent=i;
}
int ans=-1;
int N;

void init(){
    ans=-1;
    buff[1].right=-1;
    buff[1].left=-1;
    cin>>N;
    for (int i = 1; i <= N; ++i) {
        int a,l=-1,r=-1;
        string opp;
        cin>>a>>opp;
        if(opp!="+"&&opp!="-"&&opp!="/"&&opp!="*"){

        }else{
            cin>>l>>r;
        }
        handleInput(a,opp,l,r);
    }
}
double searchTree(int x){
    string opp=buff[x].data;
    if(opp!="+"&&opp!="-"&&opp!="/"&&opp!="*"){//num
        return stod(opp);
    }
    double leftResult = searchTree(buff[x].left);
    double rightResult = searchTree(buff[x].right);
    if(leftResult==INF||rightResult==INF) return INF;
    return (opp=="+"?(leftResult+rightResult)
                    :(opp=="-"?(leftResult-rightResult)
                              :(opp=="/"?(leftResult/rightResult)
                                        :(opp=="*"?(leftResult*rightResult):0))));
}

int main(int argc, char** argv)
{
    int test_case;
    int T=10;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        init();
        double ans= searchTree(1);
        cout<<"#"<<test_case<<" "<<floor(ans)<<endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}