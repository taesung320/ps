//
// Created by 윤태성 on 2022/01/10.
//

//
// Created by 윤태성 on 2022/01/10.
//
/**
 *
 */
/**
 * [제약사항]

1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.

2. 각 테스트 케이스에서 buy() 함수의 호출 횟수는 100,000 이하이다.

3. 각 테스트 케이스에서 sell() 함수의 호출 횟수는 100,000 이하이다.

4. 각 테스트 케이스에서 cancel() 함수의 호출 횟수는 200,000 이하이다.

6. 각 테스트 케이스에서 bestProfit() 함수의 호출 횟수는 100,000 이하이다.

 ##

 Parameters

mNumber : 주문 번호 (1 ≤ mNumber ≤ 200,000)

mStock : 주식 종목 (1 ≤ mStock ≤ 5)

mQuantity : 주문 수량 (1 ≤ mQuantity ≤ 1,000,000)

mPrice : 매수 희망 가격 (1 ≤ mPrice ≤ 1,000,000)
 */
#include<iostream>
#include<queue>
#include<stack>
#include <cstring>
using namespace std;
const int SELL_BUY=2;
const int SELL=0;
const int BUY=1;
const int M_STOCK=6;
const int MAX_NUM=200001;
const int INF=1e9;
int benefit[M_STOCK];
int worst[M_STOCK]={INF,INF,INF,INF,INF,INF};
bool isCancel[MAX_NUM]={};
struct node{
    int orderNum=0;
    int price=0;
    int quantity=0;
    node(int oN,int p,int q):orderNum(oN),price(p),quantity(q){}
};

struct cmp {
    bool operator()( const node &a,const node &b){
        return (a.price < b.price||(a.price==b.price&&a.orderNum>b.orderNum));
    }
};
struct cmp2 {//greater
    bool operator()( const node &a,const node &b){
        return (a.price > b.price ||(a.price==b.price&&a.orderNum>b.orderNum));
    }
};
priority_queue<node,vector<node>,cmp2> sellPq[6];
priority_queue<node,vector<node>,cmp> buyPq[6];
void init()
{
    for (int i = 0; i < 6; ++i) {
        priority_queue<node,vector<node>,cmp2>().swap(sellPq[i]) ;
        priority_queue<node,vector<node>,cmp>().swap(buyPq[i]) ;
    }
    memset(benefit,0,sizeof(benefit));
    memset(worst, 0x3f, sizeof(worst));
    memset(isCancel, 0, sizeof(isCancel));
}
void updateRecord(int mStock,int mPrice){
//    cout<<"ud "<<mStock<<" "<<mPrice<<endl;
    worst[mStock]=min(worst[mStock],mPrice);
    benefit[mStock]=max(mPrice-worst[mStock],benefit[mStock]);
}
int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    // cout<<"buy ORDER "<<mNumber<<" "<<mStock<<" "<<mQuantity<<" "<<mPrice<<endl;
    int ret=mQuantity;
    //if(sellPq[mStock].empty()) return ret;// 매수 불가한 경우
    while(!sellPq[mStock].empty()&&ret&&(mPrice>=sellPq[mStock].top().price)){
        //매도 주문이 있고, 매수할수 있고 , 매수-매도가 조건 성립
        node cur=sellPq[mStock].top();
        //  cout<<"cur "<<cur.orderNum<<" "<<cur.quantity<<" "<<cur.price<<endl;

        sellPq[mStock].pop();
        if(isCancel[cur.orderNum]){
            //취소된 주문처리
            continue;
        }
        //mStock b/w 업데이트
        updateRecord(mStock,cur.price);

        //채결 수량 파악
        if(ret>=cur.quantity){
            //    cout<<"deal "<<cur.quantity<<" with"<<cur.price<<endl;
            ret-=cur.quantity;
        }else{
            cur.quantity-=ret;
            //   cout<<"deal "<<ret<<" with"<<cur.price<<endl;

            sellPq[mStock].push(cur);
            ret=0;
        }
    }

    //주문 만큼 못산경우 , 매수 대기주문에 넣어둔다
    if(ret){
        node buyNode=node(mNumber,mPrice,ret);
        buyPq[mStock].push(buyNode);
    }

//    //sell cnt - 팔린 수량
//    waitCnt[mStock][SELL]-=(mQuantity-ret);
//    //buy cnt + 남은 수량
//    waitCnt[mStock][BUY]+=ret;
//    cout<<"ret:::"<<ret<<endl;
    return ret;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    //   cout<<"sell ORDER "<<mNumber<<" "<<mStock<<" "<<mQuantity<<" "<<mPrice<<endl;
    int ret=mQuantity;
    //if(buyPq[mStock].empty()) return ret;// 매수 불가한 경우
    while(!buyPq[mStock].empty()&&ret&&(mPrice<=buyPq[mStock].top().price)){
        //매tn 주문이 있고, 매do할수 있고 , 매수-매도가 조건 성립
        node cur=buyPq[mStock].top();
        //     cout<<"cur "<<cur.orderNum<<" "<<cur.quantity<<" "<<cur.price<<endl;
        buyPq[mStock].pop();
        if(isCancel[cur.orderNum]){
            //취소된 주문처리
            continue;
        }
        //mStock b/w 업데이트
        updateRecord(mStock,cur.price);
        //채결 수량 파악
        if(ret>=cur.quantity){
            ret-=cur.quantity;
            //        cout<<"deal "<<cur.quantity<<" with"<<cur.price<<endl;

        }else{
            cur.quantity-=ret;
            buyPq[mStock].push(cur);
            //        cout<<"deal "<<ret<<" with"<<cur.price<<endl;

            ret=0;
        }
    }
//TODO ret 만 하면됨
    //주문 만큼 못판경우 , 매도 대기주문에 넣어둔다
    if(ret){
        node sellNode=node(mNumber,mPrice,ret);
        sellPq[mStock].push(sellNode);
    }

//    //sell cnt - 팔린 수량
//    waitCnt[mStock][BUY]-=(mQuantity-ret);
//    //buy cnt + 남은 수량
//    waitCnt[mStock][SELL]+=ret;
//    cout<<"ret:::"<<ret<<endl;
    return ret;
}

void cancel(int mNumber)
{
    isCancel[mNumber]=true;
}

int bestProfit(int mStock)
{
    //   cout<<"ret::"<<benefit[mStock]<<endl;
    return benefit[mStock];
}