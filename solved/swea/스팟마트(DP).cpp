//
// Created by 윤태성 on 2022/01/24.
//

#include<iostream>
#include<cstring>
#include<algorithm>
#define A_MAX 3001
#define B_MAX 101
#define IS_CON 2
#define CON 1
using namespace std;
int cache[A_MAX][B_MAX][IS_CON][B_MAX]={};
int A[A_MAX]={};
int B[B_MAX]={};
int bSum[B_MAX]={};
int B_LEN,A_LEN;

void init(){
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(bSum, 0, sizeof(bSum));
    memset(cache, -1, sizeof(cache));
    cin>>A_LEN;
    for (int i = 1; i <= A_LEN; ++i) {
        cin>>A[i];
    }
    cin>>B_LEN;
    for (int i = 1; i <= B_LEN; ++i) {
        cin>>B[i];
    }
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
        init();
        if(B_LEN>0){
            sort(B+1, B + B_LEN+1);
            reverse(B+1, B + B_LEN+1);
        }
        bSum[0]=0;
        for (int i = 1; i <= B_LEN; ++i) {
            bSum[i]=B[i]+bSum[i-1];
        }

        cache[1][0][CON][0]=A[1];
        cache[1][0][!CON][0]=0;
        cache[0][1][CON][1]=0;
        cache[0][1][!CON][0]=0;

        for (int aIdx = 0; aIdx <= A_LEN; ++aIdx) {
            for (int bIdx = 0; bIdx <= B_LEN; ++bIdx) {
                for (int isCon = 0; isCon < IS_CON; ++isCon) {
                    for (int bCnt = 0; bCnt <= B_LEN; ++bCnt) {
                        int curVal=cache[aIdx][bIdx][isCon][bCnt];
                        if(curVal==-1)continue;
                        // cout<<aIdx<<" "<<bIdx<<" "<<isCon<<" "<<bCnt<<"  ::"<<curVal<<endl;
                        if(isCon!=CON){
                            cache[aIdx+1][bIdx][CON][bCnt]=max(cache[aIdx+1][bIdx][CON][bCnt],curVal+A[aIdx+1]);
                            cache[aIdx][bIdx+1][CON][bCnt+1]=max(cache[aIdx][bIdx+1][CON][bCnt+1],curVal);
                        }
                        cache[aIdx+1][bIdx][!CON][bCnt]=max(cache[aIdx+1][bIdx][!CON][bCnt],curVal);
                        cache[aIdx][bIdx+1][!CON][bCnt]=max(cache[aIdx][bIdx+1][!CON][bCnt],curVal);
                    }
                }
            }
        }

        int ans=0;
        for (int k = 0; k < IS_CON; ++k) {
            for (int l = 0; l <= B_LEN; ++l) {
//                cout << k << "  " << l << "  " << cache[A_LEN][B_LEN][k][l]+bSum[l]<<endl;
                ans=max(ans,cache[A_LEN][B_LEN][k][l]+bSum[l]);
            }
        }
        cout<<"#"<<test_case<<" "<<ans<<"\n";


    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}