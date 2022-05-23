#define MAX_NODE 10000

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}
int removed=0;

void init()
{
    for (int i = 0; i < MAX_NODE; ++i) {
        node[i]=Node();
    }
    nodeCnt=0;
    delete head;
    removed=0;
    head=new Node();
}
Node* getNodeAt(int i){
    Node* cur=head;
    while (i-- && cur != nullptr) {
        cur=cur->next;
    }
    return cur;
}
void addNode2Num(int data, int num)
{
    Node* target= getNodeAt(num-1);
    Node *toAdd = getNode(data);
    toAdd->next=target->next;
    target->next=toAdd;
}
void addNode2Tail(int data)
{
    addNode2Num(data, nodeCnt+1-removed);
}
void addNode2Head(int data)
{
    if(head== nullptr) {
        head->data=-1;
        head->next = getNode(data);
        return ;
    }
    addNode2Num(data, 1);
}
void removeNode(int data)
{
    Node *node = head;
    while(node->next!=nullptr){
        if(node->next->data!=data){
            node=node->next;
        }else{
            break;
        }
    }
    if(node->next== nullptr) return;
    removed++;
    node->next=node->next->next;
}

int getList(int output[MAX_NODE])
{
    Node* node=head->next;
    int idx=0;
    while (node != nullptr) {
        output[idx++]=node->data;
        node=node->next;
    }
    return idx;
}


