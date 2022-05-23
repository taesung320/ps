#include <iostream>
#include<algorithm>
#include<utility>
#include<string>
#include<cstring>
using namespace std;
typedef pair<int,int> point;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int arr[52][52]={};
bool visited[52][52]={};
int cache[52][52]={};
int N,M;
point nextPoint(point cur,int i){
    int curp=arr[cur.first][cur.second];
    int curX=cur.first+dx[i]*curp;
    int curY=cur.second+dy[i]*curp;
    curX=min(max(curX,0),N+1);
    curY=min(max(curY,0),M+1);
    return {curX,curY};
}
int dfs(point now);
bool hasCycle=false;
int main()
{
    memset(cache,-1,sizeof(cache));
    cin>>N>>M;
    for(int i=1;i<=N;i++){
        string s;
        cin>>s;
        for(int j=0;j<s.size();j++){
            if(s[j]!='H')
                arr[i][j+1]=s[j]-'0';
            else{
                arr[i][j+1]=0;
            }
        }
    }
    point startPoint={1,1};
   int ans=dfs(startPoint);
   cout<<(hasCycle?-1:ans);
   return 0;
}
int dfs(point now){
    int nowX=now.first;
    int nowY=now.second;
    int& ret=cache[nowX][nowY];
    if(ret!=-1) return ret;
    if(arr[nowX][nowY]==0) return ret=0;
    visited[nowX][nowY]=true;
    ret=0;
    for(int i=0;i<4;i++){
        point next=nextPoint(now,i);
        if(!visited[next.first][next.second]){
            ret=max(ret,1+dfs(next));
        }
        else
            hasCycle=true;
    }
    visited[nowX][nowY]=false;//모든 경로를 탐색하기 위해이 런식으로 체크를 다시 출어주게 되면 ,ㅡ cache를 써야하는 상황이 생길것같다. - 시간이 감당이 안될듯
    return ret;
}
