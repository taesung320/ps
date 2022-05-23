//TODO: sol1) 내가 풀었던것, 하지만 인덱스를 나머지로 범위 관리하는 경우에 , 나머지 연산 전에 음수가되지 않도록 주의한다
//      여기서 잘못한점 : rowOffset,colOffset가 너무 커서 +4를 해도 음수가 될때 예외가 발생했다
#include<iostream>
#include<vector>
using namespace std;
const int E=1;
const int W=2;
const int N=3;
const int S=4;
int rowDice[]={4,1,3,6};
int colDice[]={2,1,5,6};
int rowOffset=0;
int colOffset=0;
int n,m,x,y,K;
int getRowIdx(int i){
    return (i+rowOffset+4)%4;
}
int getColIdx(int i){
    return (i+colOffset+4)%4;
}
void moveDice(int d){
    if(d<=W){
        rowOffset+=(d==W?1:-1);
        rowOffset=(rowOffset+4)%4;
        colDice[getColIdx(1)]=rowDice[getRowIdx(1)];
        colDice[getColIdx(3)]=rowDice[getRowIdx(3)];
    }else{
        colOffset+=(d==S?-1:1);
        colOffset=(colOffset+4)%4;
        rowDice[getRowIdx(1)]=colDice[getColIdx(1)];
        rowDice[getRowIdx(3)]=colDice[getColIdx(3)];
    }
}
int field[20][20] = {};
int color[7]={};
int dx[] = {0,0,0,-1,1};
int dy[] = {0,1,-1,0,0};

bool check(int x,int y){
    return (0 <= x && x < n && 0 <= y && y < m);
}
int main(){

    cin>>n>>m>>x>>y>>K;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>field[i][j];
        }
    }
    vector<int> cmd(K);
    int cx=x;
    int cy=y;
    for (int i = 0; i < K; ++i) {
        cin>>cmd[i];
        int d=cmd[i];
        int nx=cx+dx[d];
        int ny=cy+dy[d];
        if(check(nx,ny)){
            cx=nx;
            cy=ny;
            moveDice(d);
            int upper= rowDice[getRowIdx(1)];
            int lower = rowDice[getRowIdx(3)];
            if(field[cx][cy]!=0){
                color[lower]=field[cx][cy];
                field[cx][cy]=0;
            }else{
                field[cx][cy]=color[lower];
            }
            cout<<color[upper]<<(i==K-1?"":"\n");
        }
    }
}
 //TODO 답.. 무식하게 하는게 오히려 정공법일수도 있다.
#include<iostream>
#include<vector>
#include<string>
using namespace std;
const int E=1;
const int W=2;
const int N=3;
const int S=4;
//동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.
//col,row 공통사항 [1]=윗면, [3]=밑면
int n,m,x,y,K;
int dice[6]={2,1,5,6,4,3};
int dx[] = {0,0,0,-1,1};
int dy[] = {0,1,-1,0,0};

int n,m,x,y,K;
//@TODO : 주사위 구현 -> 모든경우
void move_dice(int dir) {
    int ndice[6];
    switch (dir)
    {
        case 0:
            ndice[0] = dice[0];
            ndice[5] = dice[1];
            ndice[2] = dice[2];
            ndice[4] = dice[3];
            ndice[1] = dice[4];
            ndice[3] = dice[5];
            break;
        case 1:
            ndice[0] = dice[0];
            ndice[4] = dice[1];
            ndice[2] = dice[2];
            ndice[5] = dice[3];
            ndice[3] = dice[4];
            ndice[1] = dice[5];
            break;
        case 2:
            ndice[3] = dice[0];
            ndice[0] = dice[1];
            ndice[1] = dice[2];
            ndice[2] = dice[3];
            ndice[4] = dice[4];
            ndice[5] = dice[5];
            break;
        case 3:
            ndice[1] = dice[0];
            ndice[2] = dice[1];
            ndice[3] = dice[2];
            ndice[0] = dice[3];
            ndice[4] = dice[4];
            ndice[5] = dice[5];
            break;
        default:
            break;
    }
    for (int i = 0; i < 6; ++i) {
        dice[i] = ndice[i];
    }
}
int field[20][20] = {};
//주사위 인덱스에 해당하는 색깔
int color[7]={};
bool check(int x,int y){
    return (0 <= x && x < n && 0 <= y && y < m);
}
void test(int k,string progress){
    if(progress.size()>10)return ;
    moveDice(k);
    moveDice(k-1);
    int upper1=dice[1];
    int lower1=dice[3];
    int upper2=rowDice[getRowIdx(1)];
    int lower2=rowDice[getColIdx(3)];
    if(upper1!=upper2||lower1!=lower2){
        cout<<"at"<<progress<<endl;
        cout<<"diff\tu1\tu2\tl1\tl2\n";
        cout<<"diff\t"<<upper1<<"\t"<<upper2<<"\t"<<lower1<<"\t"<<lower2<<endl;
    }
    for(int i=1;i<=4;i++){
        string next=progress;
        next.push_back('0'+i);
        test(i,next);
    }
    int nextD=0;
    if(k==E) nextD=W;
    if(k==W) nextD=E;
    if(k==S) nextD=N;
    if(k==N) nextD=S;
    moveDice(nextD);
    move_dice(nextD-1);
}
int main(){
        test(1,"");
//    cin>>n>>m>>x>>y>>K;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            cin>>field[i][j];
//        }
//    }
//    int cx=x;
//    int cy=y;
//    int d=0;
//    for (int i = 0; i < K; ++i) {
//        cin>>d;
//        int nx=cx+dx[d];
//        int ny=cy+dy[d];
//        // cout<<nx<<" "<<ny<<endl;
//        if(check(nx,ny)){
//            cx=nx;
//            cy=ny;
//            move_dice(d-1);//주사위 굴림
//            //위 아래면
//            int upper= dice[1];
//            int lower = dice[3];
//            if(field[cx][cy]!=0){
//                /**
//                *  0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.
//                */
//                color[lower]=field[cx][cy];
//                field[cx][cy]=0;
//            }else{
//                /**
//                *  주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다.
//                */
//                field[cx][cy]=color[lower];
//            }
//            cout<<color[upper]<<(i==K-1?"":"\n");
//        }
//    }
}