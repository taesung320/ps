
#include<iostream>
#include<cstring>

#define MAXB 500001

using namespace std;
typedef unsigned long long ll;

ll getKey(string s,int a){
    ll ret=0;
    for (int i = 0; i < s.size(); ++i) {
        ret += ((ret*a)+ (s[i]));
    }
    return (ret);
}
ll pow2[MAXB];
ll pow3[MAXB];
string S,B;
int ans;
ll B_key;
ll B_key2;
void init(){
    ans=0;
    cin>>S>>B;
    B_key= getKey(B,1);
    B_key2= getKey(B,32);
}

void solve(){
    ll key = getKey(S.substr(0, B.size()),1);
    ll key2 = getKey(S.substr(0, B.size()),32);
    for (int i = 0; i+B.size() <= S.size(); ++i) {//+S[i]했을떄 변하는 해시값 가지고있기
        if((key==B_key)&&(key2==B_key2)){//TODO 충돌처리 1) chaining , 2) another hash
            ans++;
        }
        if(i+B.size() ==S.size())continue;
        key=(key-(pow2[B.size()-1]*(S[i])))*2+S[i+B.size()];
        key2=(key2-(pow3[B.size()-1]*(S[i])))*33+S[i+B.size()];
        // cout<<key<<" == "<<getKey(S.substr(i+1,B.size()))<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int test_case;
    int T;
    cin>>T;
    ll x=1;
    ll y=1;
    for (int i = 0; i < MAXB; ++i) {
        pow2[i]=x;
        pow3[i]=y;
        x*=2;
        y+=((y<<5));
    }
    for(test_case = 1; test_case <= T; ++test_case)
    {
        init();
        solve();
        cout<<"#"<<test_case<<" "<<ans<<"\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}