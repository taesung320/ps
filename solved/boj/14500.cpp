//
// Created by 윤태성 on 2021/12/16.
//

#include <iostream>
#include <vector>
using namespace std;

int N,M;
int field[500][500] = {};
int ans=0;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool check(int i,int j){
    return (0 <= i && i < N && 0 <= j && j < M);
}
pair<int,int> curve(int d){
    if (d < 2) {
        return {2,3};
    }else{
        return {0,1};
    }
}
void blue(int i,int j);
void yellow(int i,int j);
void orange(int i,int j);
void pink(int i,int j);
void green(int i,int j);
void fnc(int i,int j){
    blue(i,j);
    yellow(i,j);
    pink(i,j);
    orange(i,j);
    green(i,j);
}
int main(){
    cin>>N>>M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin>>field[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
//            cout<<"check fnc---------for"<<i<<" "<<j<<endl;
            fnc(i,j);
        }
    }
    cout<<ans;
}
void blue(int i,int j){
    for (int k = 0; k < 4; ++k) {
        int tot=0;
        for (int l = 0; l <4 ; ++l) {
            int cx=i+dx[k]*l;
            int cy=j+dy[k]*l;
            // cout<<"blue "<<cx<<" "<<cy<<" tot:"<<tot<<endl;
            if(check(cx,cy)){
                tot+=field[cx][cy];
            }else{
                tot=0;
//                cout<<"--!"<<endl;
                break;
            }
            if (l == 3) {
                ans=max(ans,tot);
//                cout<<"tot "<<tot<<endl;
                tot=0;
//                cout<<"--"<<endl;
            }
        }
    }
}
void yellow(int i,int j){
    if(!check(i+1,j)) return;
    if(!check(i,j+1)) return;
    if(!check(i+1,j+1)) return;
    ans=max(ans,field[i][j]+field[i+1][j]+field[i][j+1]+field[i+1][j+1]);
//    cout<<"yellow "<<i<<" "<<j<<" "<<field[i][j]+field[i+1][j]+field[i][j+1]+field[i+1][j+1]<<endl;
}
void orange(int i,int j){
    for (int k = 0; k < 4; ++k) {
        int tot=0;
        for (int l = 0; l < 3; ++l) {
            int cx=i+dx[k]*l;
            int cy=j+dy[k]*l;
//            cout<<"orange "<<cx<<" "<<cy<<" tot:"<<tot<<endl;
            if(check(cx,cy)){
                tot+=field[cx][cy];
            }else{
                tot=0;
//                cout<<"--!"<<endl;
                break;
            }
            if (l == 2) {
                pair<int,int> nd=curve(k);
                if(check(cx+dx[nd.first],cy+dy[nd.first])){
//                    cout<<"tot :: "<<tot+field[cx+dx[nd.first]][cy+dy[nd.first]]<<endl;
                    ans=max(ans,tot+field[cx+dx[nd.first]][cy+dy[nd.first]]);
                }
                if(check(cx+dx[nd.second],cy+dy[nd.second])){
//                    cout<<"tot :: "<<tot+field[cx+dx[nd.first]][cy+dy[nd.first]]<<endl;
                    ans=max(ans,tot+field[cx+dx[nd.second]][cy+dy[nd.second]]);
                }
                tot=0;
//                cout<<"--"<<endl;
            }

        }
    }
}
void pink(int i,int j){
    for (int k = 0; k < 4; ++k) {
        int tot=0;
        for (int l = 0; l < 3; ++l) {
            int cx=i+dx[k]*l;
            int cy=j+dy[k]*l;
//            cout<<"pink "<<cx<<" "<<cy<<" tot:"<<tot<<endl;
            if(check(cx,cy)){
                tot+=field[cx][cy];
            }else{
                tot=0;
//                cout<<"--!"<<endl;
                break;
            }
            if (l == 1) {
                pair<int,int> nd=curve(k);
                int temp1=0,temp2=0;
                if(check(cx+dx[nd.first],cy+dy[nd.first])){
                    temp1=(tot+field[cx+dx[nd.first]][cy+dy[nd.first]]);
                }
                if(check(cx+dx[nd.second],cy+dy[nd.second])){
                    temp2=(tot+field[cx+dx[nd.second]][cy+dy[nd.second]]);
                }
                tot=max(temp1,temp2);
            }
            if(l==2){
//                cout<<"tot :: "<<tot <<endl;
                ans=max(ans,tot);
//                cout<<"--"<<endl;
                tot=0;
            }
        }
    }
}
void green(int i,int j){
    for (int k = 0; k < 4; ++k) {
        int tot=0;
        for (int l = 0; l < 2; ++l) {
            int cx=i+dx[k]*l;
            int cy=j+dy[k]*l;
//            cout<<"green "<<cx<<" "<<cy<<" tot:"<<tot<<endl;
            if(check(cx,cy)){
                tot+=field[cx][cy];
            }else{
                tot=0;
//                cout<<"--"<<endl;
                break;
            }
            if (l == 1) {
                pair<int,int> nd=curve(k);
                if(check(cx+dx[nd.first],cy+dy[nd.first])){
                    int temp=field[cx+dx[nd.first]][cy+dy[nd.first]];
                    int nx=cx+dx[nd.first]+dx[k];
                    int ny=cy+dy[nd.first]+dy[k];
                    if(check(nx,ny)){
                        temp+=field[nx][ny];
                        ans=max(ans,tot+temp);
//                        cout<<"tot :: "<<tot+temp<<endl;
                    }
                }
                if(check(cx+dx[nd.second],cy+dy[nd.second])){
                    int temp=field[cx+dx[nd.first]][cy+dy[nd.first]];
                    int nx=cx+dx[nd.first]+dx[k];
                    int ny=cy+dy[nd.first]+dy[k];
                    if(check(nx,ny)){
                        temp+=field[nx][ny];
                        ans=max(ans,tot+temp);


//                        cout<<"tot :: "<<tot+temp<<endl;
                    }
                }
                //  cout<<"--"<<endl;
                tot=0;
            }
        }
    }
}

/**
* 5 5
1 2 3 4 5
5 4 3 2 1
2 3 4 5 6
6 5 4 3 2
1 2 1 2 1
*/