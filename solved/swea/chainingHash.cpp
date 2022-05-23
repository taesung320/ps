//
// Created by 윤태성 on 2022/02/08.
//

#include<iostream>
#include<cstring>
#define HASH_SIZE (1 << 18)
#define MAXN 100000
#define DIV (HASH_SIZE - 1)
using namespace std;
typedef unsigned long long ll;
int buff_cnt;
int getKey(string s){
    ll ret=5381;
    for (int i = 0; i < s.size(); ++i) {
        ret += ((ret << 5) + ret + (s[i] - 'a'+1));
    }
    return (int)(ret&DIV);
}
struct node{
    string key="";
    node* next= nullptr;
    node* allocSelf(string key,node* next){
        this->key=key;
        this->next=next;
        return this;
    }
    node* getPrevNode(string key){
        node* cur=this;
        while (cur->next != nullptr) {
            if (cur->next->key == key) {
                break;
            }
            cur = cur->next;
        }
        return cur;
    }
};
node buff[MAXN];
node hashTable[HASH_SIZE];

node* find(string key){
    int target = getKey(key);
    node* prev=hashTable[target].getPrevNode(key);
    return prev;
}
void addHash(string key){
    int target = getKey(key);
    node* prev=hashTable[target].getPrevNode(key);
    prev->next = buff[buff_cnt++].allocSelf(key, prev->next);
}

int N,M;
int solve(){
    buff_cnt=0;
    memset(hashTable, 0, sizeof(hashTable));
    cin>>N>>M;
    string s;
    int ans=0;
    for (int i = 0; i < N; ++i) {
        cin>>s;
        addHash(s);
    }
    for (int i = 0; i < M; ++i) {
        cin>>s;
        node* check=find(s);
        if(check->next!= nullptr) ans++;
    }
    return ans;
}
int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        int ans=solve();
        cout<<"#"<<test_case<<" "<<ans<<"\n";
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}