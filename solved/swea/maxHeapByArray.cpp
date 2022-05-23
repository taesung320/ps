
#define MAX 100001
struct User{
    int uID=-1;
    int height=-1;
};
bool compUser(User u1,User u2){//u2 higher priority
    if(u1.height!=u2.height)
        return u1.height<u2.height;
    return u1.uID>u2.uID;
}
User userHeap[MAX];
int heapSize=0;
void pushHeap(User user){

    if(heapSize==0){
        userHeap[heapSize++]=user;
        return;
    }
    userHeap[heapSize++]=user;
    int cur=heapSize-1;
    int curPar=(cur-1)/2;
    while(cur>0&&compUser(userHeap[curPar],userHeap[cur])){
        User temp=userHeap[cur];
        userHeap[cur] = userHeap[curPar];
        userHeap[curPar]=temp;
        cur=curPar;
        curPar=(cur-1)/2;
    }
    return;
}
User popHeap(){
    if(heapSize==0) return User();
    User ret=userHeap[0];
    userHeap[0] = userHeap[--heapSize];
    int cur=0;
    while((cur*2+1)<heapSize){
        int child=-1;
        if((cur*2+2)>=heapSize){
            child=cur*2+1;
        }else{
            child=(compUser(userHeap[cur*2+1],userHeap[cur*2+2])?(cur*2+2):(cur*2+1));
        }
        if(compUser(userHeap[cur],userHeap[child])){
            User temp=userHeap[cur];
            userHeap[cur] = userHeap[child];
            userHeap[child]=temp;
            cur=child;
        }else{
            break;
        }
    }
    return ret;

}
void init()
{
    heapSize=0;
}
void addUser(int uID, int height)
{
    pushHeap(User({uID, height}));
}

int getTop10(int result[10])
{
    int idx=0;
    User temp[10]={};
    while (heapSize > 0 && (idx < 10)) {
        User cur=popHeap();
        temp[idx]=cur;
        result[idx++]=cur.uID;
    }
    for (int i = 0; i < idx; ++i) {
        pushHeap(temp[i]);
    }
    return idx;
}