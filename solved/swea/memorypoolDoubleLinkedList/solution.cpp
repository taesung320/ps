#define MAX_NODE 10000

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* tail;
Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].prev = nullptr;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init()
{
    if(head!= nullptr){
        delete head;
    }
    if(tail!= nullptr){
        delete tail;
    }
//    for (int i = 0; i < MAX_NODE; ++i) {
//        node[i].next= nullptr;
//        node[i].prev= nullptr;
//        node[i].data= -1;
//    }
    nodeCnt=0;
    head=new Node;
    tail=new Node;
    head->next=tail;
    tail->prev=head;
}
Node* findNodeBySeq(int seq){//0 : head
    Node* cur=head;
    while (cur != nullptr && seq--) {
        cur=cur->next;
    }
    return cur;
}

void addBack(Node *node,int data){//node 뒤 순서 에 노드 추가
    if(node== nullptr) return;
    Node *toAdd = getNode(data);
    Node* tempNext=node->next;
    tempNext->prev=toAdd;
    toAdd->next=tempNext;
    toAdd->prev=node;
    node->next=toAdd;
}
void addNode2Head(int data)
{
    addBack(head,data);
}

void addNode2Tail(int data)
{
    addBack(tail->prev, data);
}

void addNode2Num(int data, int num)
{
    Node *target = findNodeBySeq(num - 1);
    addBack(target, data);
}

int findNode(int data)
{
    Node* cur=head;
    int ret=0;
    while (cur != nullptr && cur->data != data) {
        cur=cur->next;
        ret++;
    }
    if(cur== nullptr){
        return MAX_NODE+1;
    }
    return ret;
}

void removeNode(int data)
{
    int seq = findNode(data);
    if(seq==(MAX_NODE+1)) return ;
    Node *node = findNodeBySeq(seq);
    Node* tempNext=node->next;
    Node* tempPrev=node->prev;
    tempNext->prev=tempPrev;
    tempPrev->next=tempNext;
}

int getList(int output[MAX_NODE])
{
    int idx=0;
    Node* cur=head->next;
    while (cur != nullptr && cur != tail) {
        output[idx++]=cur->data;
        cur=cur->next;
    }
    return idx;
}

int getReversedList(int output[MAX_NODE])
{
    int idx=0;
    Node* cur=tail->prev;
    while (cur != nullptr && cur != head) {
        output[idx++]=cur->data;
        cur=cur->prev;
    }
    return idx;
}
/**
*
 *
 *
 *
 *
1 100
1 99
1 85
2 204
2 303
3 123 4
3 125 5
5 77
5 85
3 888 7
1 85
2 999
3 77 1
5 100
3 111 4
1 11
6
7
99
Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)

*/