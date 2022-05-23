//
// Created by 윤태성 on 2021/12/02.
//

#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
typedef pair<int,int> p;
bool visited[100][100]={};
vector<string> board;
vector<p> faild[26];
int ans=0;
int result_key=0;// dfs할때 모든 노드들이 공유해도 상관없다
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N,M;
void init(){
    for (int i = 0; i < 26; ++i) {
        faild[i].clear();
    }
    memset(visited, 0, sizeof(visited));
    board.clear();
    ans=0;
    result_key=0;
    N=0;
    M=0;
}
bool check(int x,int y){
    return (0 <= x && x < N && 0 <= y && y < M);
}
void testkey(int key){
    for (int i = 25; i >=0; --i) {
        //   cout<<((key&(1<<i))>0);
    }
    cout<<endl;
}
void add_result_key(char c){//열쇠 추가
    //cout<<c<<endl;
    int idx=c-'a';
    int temp_bit=1<<(idx);
    if(!(result_key&temp_bit)){
        result_key+=temp_bit;
    }
}
bool check_key(char c){
    return (result_key & (1 << (c - 'A')));
}

void dfs(int x, int y,bool is_init){//이동, 키 갱신 , 실패지점 등록(구현아직)
    //@TODO 아스키 코드 모르면 어줍잖게 덤비지말자 - 코드 줄일려고 발악 x(모르면)
    for (int i = 0; i < 4; ++i) {
        int nx = (is_init?x:x + dx[i]);
        int ny = (is_init?y:y + dy[i]);
        if (check(nx,ny)&&visited[nx][ny]==false) {
            char next_block = board[nx][ny];
            if(next_block=='*'){
                //wall
                //noting
            }else if(next_block=='.'){
                visited[nx][ny]=true;
                dfs(nx,ny,false);
            }else if (next_block == '$') {
                ans++;
                visited[nx][ny]=true;
                dfs(nx,ny,false);
            }
            else if(next_block <= 'Z'){
                //door
                if(check_key(next_block)){
                    visited[nx][ny]=true;
                    dfs(nx,ny,false);
                }else{
                    //regist fail list
                    faild[next_block-'A'].push_back({nx,ny});
                }
            } else {//무조건 이동가능
                if (next_block > 'Z') {
                    //key
                    // cout<<"get key "<<next_block<<endl;
                    add_result_key(next_block);
                }
                visited[nx][ny]=true;
                dfs(nx,ny,false);
            }
        }
        if(is_init) break;
    }
}


void try_failed_point(int i){
    // cout<<"try again "<<char('A'+i)<<endl;
    vector<p> temp=faild[i];
    faild[i].clear();
    for (int j = 0; j < temp.size(); ++j) {
        p cur = temp[j];

        // cout<<"at "<<cur.first<<" "<<cur.second<<endl;
        dfs(cur.first,cur.second,true);
    }
}
void solve(){
    //1. 가장자리 탐색 시작
    int preKey=result_key;
    for (int i = 0; i < M; ++i) {
        dfs(0,i,true);
        dfs(N - 1, i, true);
    }
    for (int i = 0; i < N; ++i) {
        dfs(i, 0, true);
        dfs(i, M - 1, true);
    }
    int postKey=result_key;
    do{
        // cout<<"one turn"<<endl;
        int temp_preKey=postKey;
        for (int i = 0; i < 26; ++i) {
            int pre_bit=(preKey&(1<<i));
            int post_bit=(postKey&(1<<i));
            if(pre_bit!=post_bit){
                try_failed_point(i);
            }
        }
        preKey=temp_preKey;
        postKey=result_key;
    }while(preKey!=postKey);
}
int main(){
    int T;
    cin>>T;
    while (T--) {
        init();
        cin>>N>>M;
        board.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> board[i];
        }
        string key;
        cin>>key;
        if (key != "0") {
            for (int i = 0; i < key.size(); ++i) {
                add_result_key(key[i]);
            }
        }
        solve();
        cout<<ans<<"\n";
    }
}
