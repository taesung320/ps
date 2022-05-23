//
// Created by 윤태성 on 2021/12/21.
//

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//TODO 빡센 구현 ? 다시해보기
//1부터 순서대로 →, ←, ↑, ↓의 의미를 갖는다.기
const int WHITE=0;
const int RED=1;
const int BLUE=2;
int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};
int N,K;
int board[13][13];
vector<int> info[13][13];
p seq[13]={};
int seq_d[13]={};
bool fin=false;
bool is_finished(){
    return fin;
}
//1부터 순서대로 →, ←, ↑, ↓의 의미를 갖는다.
void reverseDir(int i){
    int d=seq_d[i];
    int nextD=((d==1?2:(d==2?1:(d==3?4:(d==4?3:3)))));
    seq_d[i]=nextD;
}
p getNext(int i){
    int cx=seq[i].first;
    int cy=seq[i].second;
    int d=seq_d[i];
    int nx=cx+dx[d];
    int ny=cy+dy[d];
    if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N) || board[nx][ny] == BLUE) {
        return {-1,-1};
    } else {
        return {nx,ny};
    }
}
void printV(vector<int> v){
    for (int i = 0; i < v.size(); ++i) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
void move(int cx,int cy,int nx,int ny,int loc){
    vector<int>& nextV=info[nx][ny];
    vector<int>& curV=info[cx][cy];
    for (int i = loc; i < curV.size(); ++i) {
        nextV.push_back(curV[i]);
        seq[curV[i]]={nx,ny};
    }
    if((nextV.size()>=4))
        fin=true;
    int s=curV.size()-loc;
    while(s--){
        curV.pop_back();
    }
}
void turn(int i){
    int cx=seq[i].first;
    int cy=seq[i].second;
    vector<int> curV=info[cx][cy];
    int loc=-1;
    int offset=0;
    for (int j = 0; j < curV.size(); ++j) {
        if(curV[j]==i){
            loc=j;
            break;
        }
    }
    if(loc==-1) {
        //    cout<<"!!";
        return ;
    }
    p next= getNext(i);
    int nx=next.first;
    int ny=next.second;
//    cout<<"\n-------\n"<<cx<<" "<<cy<<" --> "<<nx<<" "<<ny<<endl;
//    cout<<"cur\n";
    //  printV(curV);

    if(nx==-1){
        //재시도,실패시 이동안함
        reverseDir(i);
        p next2= getNext(i);
        int nx2=next2.first;
        int ny2=next2.second;
//        cout<<"retry"<<nx2<<" "<<ny2<<endl;
        if(nx2==-1) return ;
        //다음이 레드일때 구현 해야함
        offset=info[nx2][ny2].size();
        move(cx,cy,nx2,ny2,loc);
        if (board[nx2][ny2] == RED) {
            reverse(info[nx2][ny2].begin()+offset,info[nx2][ny2].end());
        }
//        cout << "next\n";
//        printV(info[nx2][ny2]);
    }else{
        offset=info[nx][ny].size();
        move(cx,cy,nx,ny,loc);
        if (board[nx][ny] == RED) {
            //한번 뒤집기
            reverse(info[nx][ny].begin()+offset,info[nx][ny].end());
        }
//        cout << "next\n";
//        printV(info[nx][ny]);
    }

}
int main(){
    cin>>N>>K;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin>>board[i][j];
        }
    }
    for (int i = 1; i <= K; ++i) {
        int x,y,d;
        cin>>x>>y>>d;
        seq[i]={x,y};
        seq_d[i]=d;
        info[x][y].push_back(i);
    }
    int ans=0;
    while (ans <= 1000) {
        if(is_finished()){
            cout<<ans;
            return 0;
        }
        ans++;
        for (int i = 1; i <= K; ++i) {
            // cout<<"turn"<<i<<endl;
            turn(i);

        }
    }
    cout<<-1;
}



