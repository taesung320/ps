#include<iostream>
using namespace std;
bool visited[51][51]={};
int field[51][51]={};
int N;
int ans=2500;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int n_dir[4][2]={
        {3,1},
        {2,0},
        {3,1},
        {2,0}
};
void init(int n){
    ans=2500;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j]=false;
            field[i][j]=0;
        }
    }
}
bool check(int x,int y){
    return (0<=x&&x<N&&0<=y&&y<N);
}
void set_ans(int x,int y,int income,int cnt){
    // cout<<x<<" , "<<y<<" d: "<<income<<" c: "<<cnt<<endl;
    if(x+y+cnt>=ans){// TODO 다음 식의 의미이해와 활용
        // visited[x][y]=false;
        return ;
    }
    if(x==0&&y==0&&(income==2&&field[x][y]<=2||income==3&&field[x][y]>2)){
        ans=min(ans,cnt);
        return ;
    }
    visited[x][y]=true;
    if(field[x][y]<=2){
        int nx=x+dx[income];
        int ny=y+dy[income];
        if(check(nx,ny)&&!visited[nx][ny]&&field[nx][ny]){
            set_ans(nx,ny,income,cnt+1);
        }
    }else{
        for (int i = 0; i < 2; ++i) {
            int next_dir=n_dir[income][i];
            int nx=x+dx[next_dir];
            int ny=y+dy[next_dir];
            if(check(nx,ny)&&!visited[nx][ny]&&field[nx][ny]){
                set_ans(nx,ny,next_dir,cnt+1);
            }
        }
    }
    visited[x][y]=false;
    return ;
}
int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        cin>>N;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin>>field[i][j];
            }
        }
        // field[N-1][N]=1;
        //TODO 도착점부터 탐색 시작 - 무슨 차이인지는 잘 모르겠음
        visited[N-1][N-1]=true;
        set_ans(N-1,N-1,2,1);
        cout<<"#"<<test_case<<" "<<ans<<endl;
        init(N+1);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
/**
*
 * #include <iostream>
#define MAX 52

int n;
int map[MAX][MAX];
int visit[MAX][MAX];
int dp[MAX][MAX][4];
int ans;

using namespace std;

enum dir
{
    LEFT, RIGHT, UP, DOWN,
};

void init()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                dp[i][j][k] = 21e8;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            visit[i][j] = 0;
    }
    ans = 21e8;
}
int res = 0;


void getmin(int y, int x, int pos, int cnt)
{
    if (y == n && x == n) {
        if (pos == UP && map[y][x] == 6) {
            res = cnt + 1;
            if (ans > res) ans = res;
            return;
        }
        if (pos == LEFT && map[y][x] == 1) {
            res = cnt + 1;
            if (ans > res) ans = res;
            return;
        }
    }
    if (y == 1 && x == 1) {
        if (pos == RIGHT && (map[y][x] == 0 || map[y][x] == 1)) {
            res = cnt + 1;
            if (ans > res) ans = res;
            return;
        }
        if (pos == DOWN && (map[y][x] > 1)) {
            res = cnt + 1;
            if (ans > res) ans = res;
            return;
        }
    }
    if (dp[y][x][pos] < cnt) return;
    if (y <= 0 || x <= 0 || y > n || x > n) return;
    if (visit[y][x] || map[y][x] == 0) return;

    visit[y][x] = 1;
    if (map[y][x] == 1 || map[y][x] == 2) {
        if (pos == LEFT) getmin(y, x + 1, LEFT, cnt + 1);
        if (pos == RIGHT) getmin(y, x - 1, RIGHT, cnt + 1);
        if (pos == UP) getmin(y + 1, x, UP,cnt+1);
        if (pos == DOWN) getmin(y - 1, x, DOWN, cnt + 1);
    }
    else {
        if (pos < UP) {
            //left, right
            getmin(y - 1, x, DOWN, cnt + 1);
            getmin(y + 1, x, UP, cnt + 1);
        }
        else {
            //up, down
            getmin(y, x - 1, RIGHT, cnt + 1);
            getmin(y, x + 1, LEFT, cnt + 1);
        }
    }
    dp[y][x][pos] = cnt;
    visit[y][x] = 0;
}

int dfs(int y, int x, int pos)
{
    //cout << y << ' ' << x << ' ' << pos << ' ' <<  dp[y][x][pos] << '\n';
    //pos 어디서 들어오나.
    if (y == n && x == n) {
        if (pos == LEFT && (map[y][x] == 1 || map[y][x] == 2)) return 1;
        if (pos == UP && (map[y][x] != 1 && map[y][x] != 2)) return 1;
    }
    //if (y == 1 && x == 1 && pos == LEFT) return 1;
    if (map[y][x] == 0 || visit[y][x]) return 21e8;
    if (y <= 0 || x <= 0 || y > n || x > n) return 21e8;
    if (dp[y][x][pos]) return dp[y][x][pos];

    //cout << "enter " << y << ' ' << x << ' ' << pos <<' ' <<  map[y][x] << ' ' << '\n';
    if (pos == LEFT) {
        int mini = 21e8;
        int a(mini), b(mini), c(mini);
        visit[y][x] = 1;
        if (map[y][x] == 1 || map[y][x] == 2) {
            a = dfs(y, x + 1, pos);
        }
        else {
            b = dfs(y-1,x, UP); //4번
            c = dfs(y+1, x, DOWN);//5번
        }
        mini = a;
        if (mini > b) mini = b;
        if (mini > c) mini = c;
        dp[y][x][pos] = mini+1;
        visit[y][x] = 0;
    }
    else if (pos == RIGHT) {
        int mini = 21e8;
        int a(mini), b(mini), c(mini);
        visit[y][x] = 1;
        if (map[y][x] == 1 || map[y][x] == 2) {
            a = dfs(y, x - 1, pos);
        }
        else {
            b = dfs(y+1,x, DOWN);       //3번
            c = dfs(y-1, x, UP);    //6번
        }

        mini = a;
        if (mini > b) mini = b;
        if (mini > c) mini = c;
        dp[y][x][pos] = mini+1;
        visit[y][x] = 0;
    }
    else if (pos == UP) {
        int mini = 21e8;
        int a(mini), b(mini), c(mini);
        visit[y][x] = 1;
        if (map[y][x] == 1 || map[y][x] == 2) {
            a = dfs(y- 1, x, pos);
        }
        else {
            b = dfs(y , x+1, LEFT);     //6번
            c = dfs(y , x-1, RIGHT);    //5번
        }

        mini = a;
        if (mini > b) mini = b;
        if (mini > c) mini = c;
        dp[y][x][pos] = mini+1;
        visit[y][x] = 0;
    }
    else if (pos == DOWN) {
        int mini = 21e8;
        int a(mini), b(mini), c(mini);
        visit[y][x] = 1;
        if (map[y][x] == 1 || map[y][x] == 2) {
            a = dfs(y + 1, x, pos);
        }
        else {
            b = dfs(y , x+1, LEFT); //3번
            c = dfs(y , x-1, RIGHT); //4번

        }
        mini = a;
        if (mini > b) mini = b;
        if (mini > c) mini = c;
        dp[y][x][pos] = mini+1;
        visit[y][x] = 0;
    }
    cout << "update" << y << ' ' << x<<' ' << pos << ' ' << dp[y][x][pos] << '\n';
    return dp[y][x][pos];
}

int main()
{
    int tc;
    cin >> tc;
    for (int i = 1; i <= tc; i++)
    {
        init();

        //int ans = dfs(1, 1, LEFT);
        dp[1][1][LEFT] = 1;
        getmin(1, 1, LEFT, 0);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    dp[i][j][k] = 21e8;
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                visit[i][j] = 0;
        }
        dp[n][n][map[n][n]] = 1;
        getmin(n, n, RIGHT, 0);

        cout << "#" << i << ' ' << ans << '\n';
    }

    return 0;
}
  TODO 이해하기
*/