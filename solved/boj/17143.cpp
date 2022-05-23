#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<string>
using namespace std;
typedef pair<int,int> pir;
struct shark {
    int r=0;
    int c=0;
    int s=0;
    int d=0;
    int z=0;
    shark(){};
    shark(int r, int c, int s, int d, int z) : r(r), c(c), s(s), d(d), z(z) {};
};
map<pir,pir> shark_map;
vector<shark> sVec;
const int dx[] = {0, -1, 1, 0, 0};
const int dy[] = {0, 0, 0, 1, -1};
bool is_dead[10001]={};
int R,C,M;
bool check(int r,int c){
    return (1 <= r && r <= R && 1 <= c && c <= C);
}
int togD(int d){
    if((d%2)==1) return d+1;
    else return d-1;
}
pir get_next(shark& shk){
    int r=shk.r;
    int c=shk.c;
    int d=shk.d;
    int s=(d<3?shk.s%(2*R-2):shk.s%(2*C-2));
    int cr=r;
    int cc=c;
    //@TODO : R은 100인데 속도는 1000까지 가능 -> 불필요한 왕복 제거해야한다.(최적화),의심해야함

    while(s--){
        int nr=cr+dx[d];
        int nc=cc+dy[d];
        if (!check(nr, nc)) {
            d=togD(d);
        }
        cr=cr+dx[d];
        cc=cc+dy[d];
    }
    shk.d=d;
    return {cr,cc};
}
void kill_shark(int i){
    is_dead[i]=true;
    //  cout<<"kill No."<<i<<endl;
}
int take_shark(int i){
    for (int j = 1; j <=R; ++j) {
        if (shark_map.find({j, i}) != shark_map.end()) {
            pir temp=shark_map[{j,i}];
            if(is_dead[temp.second]) continue;
            kill_shark(temp.second);
            return temp.first;
        }
    }
    // cout<<"no kill"<<endl;
    return 0;
}
char t[]={' ','U','D','R','L'};
void move_shark(shark& shk,int i){
    //getNext
    //kill with map
    // cout<<"move start No."<<i<<") "<<shk.r<<" "<<shk.c<<" "<<t[shk.d];
    pir next= get_next(shk);
    // cout<<" s:"<<shk.s<<" to"<<next.first<<" "<<next.second<<"/d:"<<t[shk.d]<<endl;
    int nr=next.first;
    int nc=next.second;
    if (shark_map.find({nr,nc}) != shark_map.end()) {
        if (shark_map[{nr, nc}].first > shk.z) {
            //shk die
            kill_shark(i);
        }else{
            //shk kill
            kill_shark(shark_map[{nr,nc}].second);
            shk.r=nr;
            shk.c=nc;
            shark_map[{nr,nc}]={shk.z,i};
        }
    }else{
        shk.r=nr;
        shk.c=nc;
        shark_map[{nr,nc}]={shk.z,i};
    }
}
int main(){
    cin >> R >> C >> M;
    sVec.resize(M + 1);
    for (int i = 1; i <=M ; ++i) {
        shark& temp=sVec[i];
        cin>>temp.r>>temp.c>>temp.s>>temp.d>>temp.z;
        shark_map[{temp.r,temp.c}]={temp.z,i};
    }
    int turn=0;
    int ans=0;
    while(++turn<=C){
        ans+= take_shark(turn);
        shark_map.clear();
        for (int i = 1; i <= M; ++i) {
            if(is_dead[i]==false)
                move_shark(sVec[i],i);
        }
    }
    cout<<ans<<endl;
}
//
// Created by 윤태성 on 2021/12/07.
//

