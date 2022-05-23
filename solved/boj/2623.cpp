#include<iostream>
#include<vector>
#include <queue>
using namespace std;
int N,M;
vector<vector<int>> edge;
bool bEdge[1001][1001] = {};
int inDg[1001] = {};
vector<int> topolo(){
    vector<int> ret;
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (inDg[i]==0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ret.push_back(cur);
        for (int i = 0; i < edge[cur].size(); ++i) {
            int next=edge[cur][i];
            inDg[next]--;
            if (inDg[next] == 0) {
                q.push(next);
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        if (inDg[i]!=0) {
            vector<int> temp;
            return temp;
        }
    }
    return ret;
}
int main(){
    cin>>N>>M;
    edge.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        vector<int> temp_v;
        int T;
        cin>>T;
        for (int j = 0; j <T ; ++j) {
            int x;
            cin>>x;
            temp_v.push_back(x);
        }
        for (int j = 0; j < temp_v.size(); ++j) {
            int pre = temp_v[j];
            for (int k = j+1; k < temp_v.size(); ++k) {
                int post = temp_v[k];
                if (bEdge[post][pre]) {
                    cout<<0;return 0;
                }else{
                    if (bEdge[pre][post] == false) {
                        inDg[post]++;
                        bEdge[pre][post]=true;
                        edge[pre].push_back(post);
                    }
                }
            }
        }
    }
    vector<int> ans = topolo();
    if (!ans.size()) {
        cout<<0<<endl;
        return 0;
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << "\n";
    }
}
