//
// Created by 윤태성 on 2022/02/20.
//

#define MAX_N (10000)
#define MAX_STR_LEN (13)

#include<string>
#include<vector>
#include <map>
#include<cstring>
#include<algorithm>

using namespace std;

struct team_node {
    int day = -1;
    int s_h = 0;
    int s_m = 0;
    int e_h = 0;
    int e_m = 0;
    int time_cost = 0;

    bool operator()(const team_node &a, const team_node &b) {
        if (a.day != b.day)
            return a.day < b.day;
        if (a.s_h != b.s_h)
            return a.s_h < b.s_h;
        if(a.s_m!=b.s_m)
            return a.s_m < b.s_m;
        return a.time_cost<b.time_cost;
    }
};

inline pair<int, int> get_end_time(int sh, int sm, int tcost) {
    return {sh + (sm + tcost - 1) / 60, (sm + tcost - 1) % 60};
}

int team_cnt;
int mem_cnt;
bool team_rel[3001][3001];
vector<int> team_list[10001];
team_node team[3001];
map<string, int> mem_idx;
map<string, int> team_idx;
int cur_day;
void init(int N, char mName[][MAX_STR_LEN]) {
    cur_day = 0;
    team_cnt = 0;
    mem_cnt = N;
    memset(team_rel, 0, sizeof(team_rel));
    memset(team, -1, sizeof(team));
    memset(team_list, 0, sizeof(team_list));
    mem_idx={};
    team_idx={};

    for (int i = 0; i < mem_cnt; ++i) {
        mem_idx.insert({mName[i], i});
    }
}
void createTeam(char mTeamName[], int M, char mName[][MAX_STR_LEN]) {
    string temp=mTeamName;
    team_idx.insert({temp, team_cnt++});
    int t_idx = team_cnt - 1;
    for (int i = 0; i < M; ++i) {
        string t=mName[i];
        int m_idx = mem_idx[t];
        for (int j = 0; j < team_list[m_idx].size(); ++j) {
            team_rel[team_list[m_idx][j]][t_idx] = true;
            team_rel[t_idx][team_list[m_idx][j]] = true;
        }
        team_list[m_idx].push_back(t_idx);
    }
}
int bookMeeting(char mTeamName[], int mMinutes) {
    int cur_week = cur_day / 7 + 1;
    int day = cur_day % 7;
    if (day >= 5) {
        day = 0;
        cur_week++;
    }
    vector<team_node> temp;
    string temp_s=mTeamName;
    int t_idx = team_idx[temp_s];
    team[t_idx]={-1,-1,-1,-1,-1};
    for (int i = 0; i < team_cnt; ++i) {
        if (team_rel[t_idx][i]) {
            int crash = i;
            team_node cur_tm = team[crash];
            if (team[crash].day != -1) {
                cur_tm.day = (5 + cur_tm.day + -day) % 5;
                temp.push_back(cur_tm);
            }
        }
    }
    temp.push_back({4,9,0,0,0,0});
    sort(temp.begin(), temp.end(),team_node());
    int tmp_sh = 0;
    int tmp_sm = 0;
    bool flg = temp.empty();
    int day_offset = 0;
    int mgn_sh=9;
    int mgn_sm=0;
    int cache_h=0;
    int cache_m=0;
    if(!flg){
        for (int i = 0; i < temp.size(); ++i) {
            pair<int, int> e_time = get_end_time(tmp_sh, tmp_sm, mMinutes);
            if(day_offset>temp[i].day)continue;
            if(day_offset<temp[i].day){
                if(e_time.first<mgn_sh||(e_time.first==mgn_sh&&e_time.second==mgn_sm)){
                    flg=true;
                    break;
                }
                if (day_offset + 1 < temp[i].day) {
                    tmp_sh=0;
                    tmp_sm=0;
                    day_offset++;
                    flg=true;
                    break;
                }
                if(day_offset+1==temp[i].day){
                    tmp_sh=0;
                    tmp_sm=0;
                    cache_h=0;
                    cache_m=0;
                    e_time = get_end_time(tmp_sh, tmp_sm, mMinutes);
                    day_offset=temp[i].day;
                }
            }
            if (e_time.first < temp[i].s_h || (e_time.first == temp[i].s_h && e_time.second < temp[i].s_m)) {
                flg=true;
                break;
            }else{
                day_offset=temp[i].day;
                tmp_sh=temp[i].e_h;
                tmp_sm=temp[i].e_m+1;
                if(tmp_sh<cache_h){
                    tmp_sh=cache_h;
                    tmp_sm=cache_m;
                }else if(tmp_sh==cache_h){
                    tmp_sm = max(tmp_sm, cache_m);
                }
                if(tmp_sm==60){
                    tmp_sm=0;
                    tmp_sh++;
                    if(tmp_sh==9){
                        day_offset++;
                        cache_h=0;
                        tmp_sh=0;
                    }
                }
                if(cache_h<tmp_sh){
                    cache_h=tmp_sh;
                    cache_m=tmp_sm;
                }else if(cache_h==tmp_sh){
                    cache_m=max(tmp_sm,cache_m);
                }
            }
        }
    }
    if(flg){
        team[t_idx]={
                (day+day_offset)%5,
                tmp_sh,
                tmp_sm,
                get_end_time(tmp_sh, tmp_sm, mMinutes).first,
                get_end_time(tmp_sh, tmp_sm, mMinutes).second,
                mMinutes
        };
        return (cur_week+(day+day_offset)/5)*100000+(1+team[t_idx].day)*10000+(tmp_sh+9)*100+tmp_sm;
    }else{
        return 0;
    }
}
void timeElapse(int mDays) {
    cur_day += mDays;
}