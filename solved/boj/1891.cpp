#include <string>
#include <vector>
#include <iostream>
typedef long long ll;
using namespace std;
#define MAX 1LL<<50
#define INIT 1LL<<49
char mp[]={'2','3','1','4'};
int main(){
    ll d,dx,dy;
    string s;
    cin>>d>>s>>dx>>dy;
    ll x=0;
    ll y=0;
    ll mask=INIT;
    for (int i = 0; i < d; ++i) {
        if(s[i]=='1'||s[i]=='4'){
            x+=mask;
        }
        if(s[i]=='3'||s[i]=='4'){
            y+=mask;
        }
        mask>>=1;
    }
    if(!mask)
        mask=1;
    else
        mask<<=1;
    x+=(dx * mask);
    y-=(dy * mask);
    if(0>x||x>=MAX||y<0||y>=MAX){
        cout<<-1;
        return 0;
    }
    mask=INIT;
    string ret;
    for (int i = 0; i <d; ++i) {
        ll xBit=bool(x&mask);
        ll yBit=bool(y&mask);
        ll cur=(xBit<<1)+yBit;
        ret.push_back(mp[cur]);
        mask>>=1;
    }
    cout<<ret;
}