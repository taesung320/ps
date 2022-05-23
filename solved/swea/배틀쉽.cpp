#define MISS		0
#define CARRIER		1
#define BATTLESHIP	2
#define CRUISER		3
#define SUBMARINE	4
#define DESTROYER	5
#define UNKNOWN -1
#include<cstring>
#define MAX 10
using  namespace  std;
extern int fire(int r, int c);
int resultBoard[MAX][MAX]={};
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int leng[5] = { 5, 4, 3, 3, 2 };
int minLen=2;
inline bool check(int x,int y){
    return (0 <= x && x < MAX && 0 <= y && y < MAX);
}
bool visit[10][10]={};
bool isBreaked[6]={};
bool isAttacked[10][10]={};
int bt=17;
int aimAt(int x,int y){
    if(!check(x,y)) return -2;
    if (resultBoard[x][y] == UNKNOWN) {
        resultBoard[x][y]=fire(x, y);
        if(resultBoard[x][y]>MISS){
            if(!isAttacked[x][y]){
                isAttacked[x][y]=true;
                bt--;
            }
        }
        return resultBoard[x][y];
    }else{
        return resultBoard[x][y];
    }
}
void onFindOne(int x,int y,int n){
    visit[x][y]=true;
    for (int k = 0; k < 4; ++k) {
        int nx=x+dx[k];
        int ny=y+dy[k];
        int result2= aimAt(nx,ny);
        if(result2>MISS){
            if (n == result2) {
                for (int l = 0; l <leng[n-1] ; ++l) {
                    aimAt(nx+dx[k]*l,ny+dy[k]*l);
                }
                for (int l = 0; l <leng[n-1] ; ++l) {
                    aimAt(nx-dx[k]*l,ny-dy[k]*l);
                }
                return ;
            }
            if(!visit[nx][ny]){
                onFindOne(nx, ny,result2);
            }
        }
    }
}
void init(int limit)
{
    bt=17;
    memset(isAttacked, 0, sizeof(isAttacked));
    memset(isBreaked, 0, sizeof(isBreaked));
    memset(resultBoard, -1, sizeof(resultBoard));
    memset(visit, 0, sizeof(visit));

}
void play()
{
    init(0);
    for (int i = 0; i < MAX; i=i+1) {
        int si=(4+i)%10;
        for (int j = i%2; j < MAX; j=j+2) {
            int sj=(4+j)%10;
            if(bt==0){
                return;
            }
            int result = aimAt(si, sj);
            if(result>MISS){
                onFindOne(si,sj,result);
            }
        }
    }
}


