#include <iostream>
#include <cstring> 
using namespace std;
const long long MOD = 1000000007;
const int MAX = 100 + 1;
int N, L, R;
long long cache[MAX][MAX][MAX];

 

long long numOfWays(int buildingNum, int left, int right)

{

        //기저 사례: 오름차순, 내림차순

        if ((left == 1 && right == buildingNum) || (left == buildingNum && right == 1))

                 return 1;

        //불가능한 경우

        if (buildingNum == 0 || left == 0 || right == 0)

                 return 0;

 

        long long &result = cache[buildingNum][left][right];

        if (result != -1)

                 return result;

 

        result = 0;

        //1. 좌측과 우측을 제외한 곳에 추가하면 그대로

        //2. N-1 높이를 가진 건물을 우측에 추가하면 우측에서 보이는 건물 증가

        //3. N-1 높이를 가진 건물을 좌측에 추가하면 좌측에서 보이는 건물 증가

        result = ((numOfWays(buildingNum - 1, left, right) * (buildingNum - 2)) + numOfWays(buildingNum - 1, left - 1, right) + numOfWays(buildingNum - 1, left, right - 1)) % MOD;

 

        return result;

}

 

int main(void)

{

        cin >> N >> L >> R;

       

        memset(cache, -1, sizeof(cache));

 

        cout << numOfWays(N, L, R) % MOD << endl;

 

        return 0;

}


