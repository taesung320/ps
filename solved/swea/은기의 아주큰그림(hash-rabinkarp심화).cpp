#include<iostream>
#include<string>
#include<cstring>
#define MAX 2000
using namespace std;
int H,W,N,M;
typedef unsigned long long ll;
const ll MAXS=1<<60;
ll power[MAX]={};
ll power33[MAX]={};
ll power17[MAX]={};
string child[MAX] = {};
string parent[MAX] = {};
ll parLowKey[MAX][MAX]={};
ll sub_square_key;
ll sub_square_key2;
inline ll strToHash(string s){
    ll ret=0;
    for (int i = 0; i < s.size(); ++i) {
        ret=(ret<<1)+(s[i]=='o'?1:0);
    }
    return ret;
}
inline ll squareToHash(int i,int j){
    ll ret=0;
    for (int k = 0; k < H; ++k) {
        ret+=(ret<<5)+parLowKey[i+k][j];
    }
    return ret;
}
inline ll squareToHash_sub(int i,int j){
    ll ret=0;
    for (int k = 0; k < H; ++k) {
        ret+=(ret<<4)+parLowKey[i+k][j];
    }
    return ret;
}
int ans;
void init(){
    ans=0;
    cin>>H>>W>>N>>M;
    ll square=0;
    ll square2=0;
    for (int i = 0; i < H; ++i) {
        cin >> child[i];
        square += (square << 5) + strToHash(child[i]);
        square2 += (square2 << 4) + strToHash(child[i]);
    }
    sub_square_key=square;
    sub_square_key2=square2;

    ll cur_key=0;
    for (int i = 0; i < N; ++i) {
        cin >> parent[i];
        cur_key = strToHash(parent[i].substr(0, W));
        for (int j = 0; j < M-W+1; ++j) {
            // cout<<(strToHash(parent[i].substr(j,W)) == cur_key)<<endl;
            parLowKey[i][j]=cur_key;
            if(j==(M-W)) continue;
            cur_key=((cur_key-power[W-1]*(parent[i][j]=='o'?1:0))<<1)+(parent[i][j+W]=='o'?1:0);
        }
    }
    ll cur_square_key=0;
    ll cur_square_key2=0;
    for (int i = 0; i < M - W + 1; ++i) {
        cur_square_key=squareToHash(0,i); // M-W)*(N-H
        cur_square_key2=squareToHash_sub(0,i); // M-W)*(N-H
        for (int j = 0; j < N - H + 1; ++j) {
            // cout<<(cur_square_key== squareToHash(j,i))<<endl;
            if((cur_square_key==sub_square_key)&&(cur_square_key2==sub_square_key2)){
                ans++;
            }
            if (j < (N - H)) {
                ll temp=(cur_square_key-parLowKey[j][i]*power33[H-1]);
                ll temp2=(cur_square_key2-parLowKey[j][i]*power17[H-1]);
                cur_square_key=(temp<<5)+(temp)+parLowKey[j+H][i];
                cur_square_key2=(temp2<<4)+(temp2)+parLowKey[j+H][i];
            }
        }
    }
}
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int test_case;
    int T;
    cin>>T;
    int x=1;
    int y=1;
    int z=1;
    for (int i = 0; i < MAX; ++i) {
        power[i]=x;
        power33[i]=y;
        power17[i]=z;
        x+=x;
        y+=(y<<5);
        z += (z << 4);
    }
    for(test_case = 1; test_case <= T; ++test_case)
    {
        init();
        cout<<"#"<<test_case<<" "<<ans<<"\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
