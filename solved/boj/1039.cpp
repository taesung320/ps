#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

string maxStr(string& s1,string& s2){
    return (s1 < s2 ? s2 : s1);
}
string ans;
int K;
unordered_map<string,int> strSet;
void swapIJ(string& s,int i,int j){
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}
bool flg;
void dfs(string& s,int k){
    if(k==K) return ;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i+1; j < s.size(); ++j) {
            if(i==0&&s[j]=='0') continue;
            swapIJ(s, i, j);
            if (s > ans) {
                if ((K - k - 1) % 2 == 0||flg) {
                    ans = maxStr(ans, s);
                }
            }
            if (strSet.find(s) == strSet.end()) {
                strSet.insert({s,k+1});
                dfs(s, k + 1);
            }else if(strSet[s]>k+1){
                strSet[s]=k+1;
                dfs(s,k+1);
            }
            swapIJ(s, i, j);
        }
    }
}
bool isMulti[10];
int main(){
    string s;
    cin>>s>>K;
    for (int i = 0; i < s.size(); ++i) {
        if (!isMulti[s[i] - '0']) {
            isMulti[s[i] - '0']=true;
        }else{
            flg=true;
            break;
        }
    }
    ans = (((K % 2)&&!flg) ? "0000000" : s);
    strSet.insert({s,0});
    dfs(s, 0);
    if(s.size()==2){
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                cout<<-1;
                return 0;
            }
        }
    }
    if (s.size()==1||(strSet.size() == 1&&strSet[s]!=0)) {
        cout<<-1;
        return 0;
    }
    cout<<ans;
}
/**
* 예제 입력 1
16375 1
예제 출력 1
76315
예제 입력 2
132 3
예제 출력 2
312
예제 입력 3
432 1
예제 출력 3
423
예제 입력 4
90 4
예제 출력 4
-1
예제 입력 5
5 2
예제 출력 5
-1
예제 입력 6
436659 2
예제 출력 6
966354
*/