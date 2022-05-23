#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> p;
vector<vector<p>> edge;
int N,M;
int indg[101]={};
vector<int> topology(){
    int field[101][101] = {};
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (indg[i] == 0) {
            field[i][i]=1;
            q.push(i);
        }
    }
    for (int i = 1; i <= N; ++i) {
        //여기서 이미 q가 비엇으면 사이클이 발생한것
        if(q.empty()) return {};
        int cur=q.front();
        q.pop();
        for (int j = 0; j < edge[cur].size(); ++j) {
            int next=edge[cur][j].first;
            int w=edge[cur][j].second;
            // cout<<"cur : "<<cur<<" next : "<<next<<endl;
            for (int k = 1; k <= N; ++k) {
                field[next][k]+=(w*field[cur][k]);
                // cout<<k<<"th:: "<<field[cur][k]<<" "<<field[next][k]<<endl;
            }
            indg[next]--;
            if (indg[next] == 0) {
                q.push(next);
            }
        }
    }
    vector<int> ret(N+1);
    for (int i = 1; i <= N; ++i) {
        // for (int j = 1; j <= N; ++j) {
        ret[i]+=field[N][i];
        //  }
    }
    return ret;
}

int main(){
    cin>>N>>M;
    edge.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int x,y,w;
        cin>>x>>y>>w;
        edge[y].push_back({x, w});
        indg[x]++;
    }
    vector<int> ans = topology();
    for (int i = 1; i <=N ; ++i) {
        if(ans[i]!=0)
            cout<<i<<" "<<ans[i]<<"\n";
    }
}

