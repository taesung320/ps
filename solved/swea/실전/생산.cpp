#include<queue>
#include<vector>
#include<iostream>
#include<unordered_map>
#include<cstring>
using namespace std;
#define CMD_INIT 1
#define CMD_REQUEST 2
#define CMD_STATUS 3
#define INF 1000000
int L,M;
typedef pair<int,int> p;
priority_queue<p,vector<p>,greater<>> timetable;
unordered_map<int,int> stt;
struct l_node{
    int eId=-1;
    int pId=-1;
    int time_cost=0;
    bool on_process=false;
};

queue<l_node> lineQ[555];
bool usingE[555];


void run_factory(int timestamp){
    while (!timetable.empty() && (timetable.top().first <= timestamp)) {
        int cur_time = timetable.top().first;
        while(!timetable.empty()&&(timetable.top().first == cur_time)){
            int cur_line = timetable.top().second;
            int eId=lineQ[cur_line].front().eId;
            int pId=lineQ[cur_line].front().pId;
            timetable.pop();
            stt[pId]=3;
            lineQ[cur_line].pop();
            usingE[eId]=false;
        }
        for (int i = 0; i < L; ++i) {
            if (!lineQ[i].empty()&&!lineQ[i].front().on_process) {
                int cur_eId=lineQ[i].front().eId;
                int cur_pId=lineQ[i].front().pId;
                int t_cost=lineQ[i].front().time_cost;
                if(!usingE[cur_eId]){
                    usingE[cur_eId]=true;
                    stt[cur_pId]=2;
                    timetable.push({cur_time + t_cost, i});
                    lineQ[i].front().on_process=true;
                }
            }
        }
    }
}
void init(int _L, int _M) {
    L=_L,M=_M;
    memset(usingE, 0, sizeof(usingE));
    for (int i = 0; i < L; ++i) {
        lineQ[i] = {};
    }
    timetable = {};
    stt = {};
}
int request(int tStamp, int pId, int mLine, int eId, int mTime) {
    run_factory(tStamp-1);
    lineQ[mLine].push({eId, pId,mTime,false});
    stt.insert({pId, 1});
    run_factory(tStamp);

    if (!lineQ[mLine].empty()) {
        if (lineQ[mLine].front().pId == pId && !usingE[eId]) {
            timetable.push({mTime+tStamp,mLine});
            stt[pId]=2;
            lineQ[mLine].front().on_process=true;
            usingE[eId]=true;
        }
    }

    if (lineQ[mLine].empty()) {
        return -1;
    }else if(lineQ[mLine].front().on_process){
        return lineQ[mLine].front().pId;
    }else{
        return -1;
    }
}
int status(int tStamp, int pId) {
    run_factory(tStamp);
    return stt[pId];
}
