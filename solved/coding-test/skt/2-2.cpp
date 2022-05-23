#include <iostream>
#include<queue>
#include<string>
using namespace std;
string arr[1000]={"1","2","4","3","3","4","1","5"};
string querys[1000]={"read 1 3 1 2","read 2 6 4 7","write 4 3 3 5 2","read 5 2 2 5","write 6 1 3 3 9","read 9 1 0 7"};

int N=8;
int M=6;
const int R=0;
const int W=1;
struct req{
    int rId;
    int type;
    int t1;
    int t2;
    int arg1;
    int arg2;
    string arg3;
    bool operator()(const req r1,const req r2){
        if(r1.type!=r2.type) return r1.type<r2.type;//bigger get top
        return r1.t1>r2.t1; //earlier get top
    }
};
req qry[1000]={};
typedef priority_queue<req,vector<req>,req> pq;
pq ready_pq;
req query2req(string s,int idx){
    vector<string> ret;
    string temp="";
    for(int i=0;i<s.size();i++){
        if(s[i]==' '){
            ret.push_back(temp);
            temp="";
        }else{
            temp.push_back(s[i]);
        }
    }
    ret.push_back(temp);
    ret.push_back("0");
    req rq={
            idx,
            ret[0]=="write"?W:R,
            stoi(ret[1]),
            stoi(ret[2]),
            stoi(ret[3]),
            stoi(ret[4]),
            ret[5]
    };
    return rq;

}
int tot_time;
vector<string> result_v;
struct on_proc{
    int cpu_end_at=-1;
    int cpu_query_idx=-1;
    bool operator()(const on_proc p1, const on_proc p2){
        return p1.cpu_end_at>p2.cpu_end_at;
    }
};
priority_queue<on_proc,vector<on_proc>,on_proc> cpu_pc;
int cur_time;

void cpu_work(){
    on_proc temp=cpu_pc.top();
    req cur_req=qry[temp.cpu_query_idx];
    cout<<"do "<<cur_req.rId<<endl;
    if(cur_req.type==W){
        for (int i = cur_req.arg1; i <= cur_req.arg2; i++) {
            arr[i]=cur_req.arg3;
        }
    }else{
        string temp;
        for (int i = cur_req.arg1; i <= cur_req.arg2; i++) {
            temp+=arr[i];
        }
        result_v.push_back(temp);
    }
    tot_time+=(cpu_pc.top().cpu_end_at-cur_time);
    cur_time=cpu_pc.top().cpu_end_at;
    cpu_pc.pop();
}
void timeFlow(int tStamp){
    cout<<"flow at "<<tStamp<<endl;
    if(tStamp==3){

    }
    while (!cpu_pc.empty()) {
        on_proc t_pc=cpu_pc.top();
        if(qry[t_pc.cpu_query_idx].type==R){
            while(!ready_pq.empty()&&ready_pq.top().type==R){
                cpu_pc.push({
                                    cur_time+ready_pq.top().t2,
                                    ready_pq.top().rId
                            });
                ready_pq.pop();
            }
        }
        if(cpu_pc.top().cpu_end_at > tStamp )
            break;
        cpu_work();
        if(cpu_pc.empty()){
            if(!ready_pq.empty()){
                cpu_pc.push({
                                    max(cur_time,ready_pq.top().t1)+ready_pq.top().t2,
                                    ready_pq.top().rId
                            });
                ready_pq.pop();
            }
        }
    }


}
vector<string> solve(){
    for (int i = 0; i < M; ++i) {
        qry[i] = query2req(querys[i],i);
    }
    for (int i = 0; i < M; ++i) {
        req curReq=qry[i];
        int req_at=curReq.t1;
        if(i)
            timeFlow(req_at-1);
        if(cpu_pc.empty()){
            cur_time=curReq.t1;
            cpu_pc.push({
                                curReq.t1+curReq.t2,
                                curReq.rId
                        });
        }else{
            ready_pq.push(curReq);
        }
    }
    timeFlow(1101);
    cout<<"[";
    for (int i = 0; i < result_v.size(); ++i) {
        cout<<"\""+result_v[i]+"\",";
    }
    cout<<tot_time<<"]"<<endl;
}
int main() {
    solve();
    return 0;
}
