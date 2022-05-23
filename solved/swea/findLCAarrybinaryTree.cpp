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
    int h=-1;
    int left=-1;
    int right=-1;
//    node(){};
//    node(int lc,int rc):left(lc),right(rc){};
} buff[10010];

void handleInput(int p,int c){
    //  cout<<"handle input "<<i<<" "<<data<<" "<<lc<<" "<<rc<<endl;
    buff[p].h=0;
    if(buff[p].left==-1){
        buff[p].left=c;
    }else{
        buff[p].right=c;
    }
    buff[c].parent=p;
    buff[c].h=0;
}
int V,E,A,B;
void initTree(int x){
    if(buff[x].right!=-1){
        initTree(buff[x].right);
    }
    if (buff[x].left != -1) {
        initTree(buff[x].left);
    }
    buff[x]=node({-1,-1,-1,-1});
}
void init(){
//    cout<<"1\n";
    initTree(1);
//    cout<<"2\n";
    cin>>V>>E>>A>>B;
    int p,c;
    for (int i = 1; i <= E; ++i) {
//        cout<<i<<endl;
        cin>>p>>c;
        handleInput(p, c);
    }
//    cout<<3<<endl;
}
int getDepth(int x){
    int ret=0;
    while(x!=1){
//        cout<<x<<endl;
        ret++;
        x=buff[x].parent;
    }
    //  cout<<x<<" depth:"<<ret<<endl;
    return ret;
}
int getLca(){
//    cout<<"LCA\n";
    int ap=A;
    int bp=B;
//    cout<<"A depth\n";
    int ad= getDepth(ap);
//    cout<<"B depth\n";
    int bd = getDepth(bp);
    while(ad!=bd){
        if (ad< bd) {
            bd--;
            bp = buff[bp].parent;
        }else{
            ad--;
            ap = buff[ap].parent;
        }
    }
//    cout<<ap<<" "<<bp<<endl;
    while (buff[bp].parent != buff[ap].parent) {
        bp = buff[bp].parent;
        ap = buff[ap].parent;
    }
    return buff[bp].parent;
}

int initHeight(int x){
    int ret=-1;
    if (buff[x].left != -1) {
        ret = max(ret, initHeight(buff[x].left));
    }
    if (buff[x].right != -1) {
        ret = max(ret, initHeight(buff[x].right));
    }
    // cout<<x<<" h:"<<ret+1<<endl;
    return buff[x].h=ret+1;
}
int getSizeOfTree(int x){
//    cout<<x<<endl;
    int ret=0;
    if (buff[x].left != -1) {
        ret += getSizeOfTree(buff[x].left);
    }
    if (buff[x].right != -1) {
        ret += getSizeOfTree(buff[x].right);
    }
    return ret+1;
}
int main(int argc, char** argv)
{
    int test_case;
    int T=10;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        init();
        int lca=getLca();
        cout<<"#"<<test_case<<" "<<lca<<" "<<getSizeOfTree(lca)<<endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}