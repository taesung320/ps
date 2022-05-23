#include<iostream>
#include<cstring>
using namespace std;
struct Node {
    int data=0;
    Node* prev=NULL;
    Node* next=NULL;
    Node(int data){
        this->data=data;
    }
};
struct LinkedList{
    Node* head=NULL;
    Node* tail=NULL;
    LinkedList(){
        head = new Node(0);
        tail = new Node(0);
        head->next=tail;
        tail->prev=head;
    }
    Node *getNodeAt(int i){
        Node* cur=head->next;
        while (i-- && cur != tail) {
            cur = cur->next;
        }
        return cur;
    }
    Node* remove(Node* node){
        if(node==head||node==tail) return NULL;
        Node* tempPrev=node->prev;
        Node* tempNext=node->next;
        // cout<<tempPrev<<" "<<tempNext<<endl;
        tempPrev->next=tempNext;
        tempNext->prev=tempPrev;
        return NULL;
    }
    Node* addFrontOf(Node *node,int data){
        if(node==head) return NULL;
        Node *toAdd = new Node(data);
        Node* tempPrev=node->prev;
        tempPrev->next = toAdd;
        toAdd->prev=tempPrev;
        toAdd->next=node;
        node->prev=toAdd;
        return NULL;
    }
};

int N;
int M;
int L;

char cmd;

void init(){

}
int main(int argc, char** argv)
{

    int test_case=1;
    int T=10;
    cin>>T;
    /*
       아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
       앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
       //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
       freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
       따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
       freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
       단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
    */
    //freopen("input.txt", "r", stdin);
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
//      cin>>
        cin>>N>>M>>L;
        LinkedList* ll = new LinkedList();
        for (int i = 0; i < N; ++i) {
            int x;
            cin>>x;
            ll->addFrontOf(ll->tail, x);
        }
        for (int i = 0; i < M; ++i) {
            char cmd;
            cin>>cmd;
            int x,y;
            cin>>x;
            Node* node=ll->getNodeAt(x);
            if (cmd == 'I') {
                cin>>y;
//                I 2 7 -> 2번 인덱스 앞에 7을 추가하고, 한 칸 씩 뒤로 이동한다.
                ll->addFrontOf(node,y);
            } else if (cmd == 'D') {
//                D 4 -> 4번 인덱스 자리를 지우고, 한 칸 씩 앞으로 이동한다.
                ll->remove(node);
            } else if (cmd == 'C') {
//                C 3 8 -> 3번 인덱스 자리를 8로 바꾼다.
                cin>>y;
                node->data=y;
            }
        }
        Node* node=ll->getNodeAt(L);
        if (node != ll->tail) {
            cout<<"#"<<test_case<<" "<<node->data<<endl;
        }else{
            cout<<"#"<<test_case<<" "<<-1<<endl;
        }
        Node* cur=ll->head;
        while (cur != NULL) {
            Node* temp=cur;
            cur=cur->next;
            delete temp;
        }
        delete ll;

    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/**
* 10
1 2 3 4 5 6 7 8 9 10
10
I 3 11 12 13
*/

//10
//1 2 3 4 5 6 7 8 9 10
//10
//I 3 3 11 12 13

