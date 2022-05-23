//
// Created by 윤태성 on 2022/01/31.
//

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#include<string>
#include<vector>
#define ROOT -1
using namespace std;
typedef  int nodeName;
struct node{
    node* par;
    nodeName name;
    vector<node*> children;
    node* getChild(nodeName nm){ //vec O(1~N) vs map O(log(n of child))
        for (int i = 0; i < children.size(); ++i) {
            if(children[i]== nullptr)continue;
            if (children[i]->name == nm) {
                return children[i];
            }
        }
    }
    void insertChild(node* child){ // vec O(1) vs map O(log(n of child))
        this->children.push_back(child);
    }
    void eraseChild(nodeName nm){//vec O(1~N) vs map O(log(n of child))
        for (int i = 0; i < children.size(); ++i) {
            if(children[i]== nullptr)continue;
            if (children[i]->name == nm) {
                children[i]= nullptr;
                return;
            }
        }
    }
};
typedef vector<node*> Children;
typedef pair<nodeName,node*> Child;
node* root=nullptr;

inline nodeName s2n(string str){ //T(6)
    nodeName ret=0;
    for (int i = 0; i < str.size(); ++i) {
        int temp=str[i]-'a';
        ret|=(temp<<(i*5));
    }
    return ret;
}
//5만 - 천만  200번
inline node* findNodeByPath(string path){ //패스로 노드 포인터 찾기 최대 해봣자 2천
    node* ret=root;
    if(path=="/") {
        return ret;
    }
    nodeName temp=0;//문자열을 숫자로 담기위한거
    int offset=0;
    for (int i = 1; i < path.size(); ++i) {
        if (path[i] == '/') {
            ret = ret->getChild(temp);
            temp = 0;
            offset=0;
        } else {
            temp |= ((path[i]-'a')<<((offset)*5));//문자열에 문자를 하나씩 변환
            offset++;
        }
    }
    return ret;
}
void removeDir(node* cur){//동적 할당 해재 시간때매 비움 근데 채움 근데 시간초과

    delete cur;
}
void init(int n) {
    if(root!= nullptr){
        removeDir(root);
        root=nullptr;
    }
    root = new node({nullptr, ROOT,vector<node*>()});
}
void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    nodeName nm=s2n(name);
    node *findNode = findNodeByPath(path);
    node *newNode= new node({findNode,nm,Children ()});
    findNode->insertChild(newNode);
}
void cmd_rm(char path[PATH_MAXLEN + 1]) {
    node *findNode = findNodeByPath(path);
//    nodeName tempName=findNode->name;
//    node* tempPar=findNode->par;
    findNode->par->eraseChild(findNode->name);
}
void copy(node* orn,node* cpy){
    cpy->name=orn->name; // 원본갑 복사
    for (int i=0;i<orn->children.size();i++) {
        if(orn->children[i]== nullptr) continue;
        node *newChild = new node({cpy,orn->children[i]->name, Children()});//자식 복사
        cpy->insertChild(newChild); //복사본에 복사한 자식 삽입
        copy(orn->children[i], newChild);// 원본자식1과 복사본에 삽입된 자시고가 복사
    }
}
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    node *srcNode = findNodeByPath(srcPath);
    node *dstNode = findNodeByPath(dstPath);
    node *newNode=new node({dstNode,srcNode->name,Children ()});
    dstNode->insertChild( newNode);//타켓 밑에 새로만들고 복사시작
    copy(srcNode, newNode);
}
void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    node *findNode = findNodeByPath(srcPath);
    findNode->par->eraseChild(findNode->name);
    node *findDst = findNodeByPath(dstPath);
    findNode->par=findDst;
    findDst->insertChild(findNode);
}
int findNodeCnt(node* cur){// need cache아마도
    if(cur== nullptr) return 0;
    int ret=0;
    for (int i=0;i<cur->children.size();i++) {
        ret += findNodeCnt(cur->children[i]);
    }
    return ret+1;
}
int cmd_find(char path[PATH_MAXLEN + 1]) {
    node *findNode = findNodeByPath(path);
    int ret = findNodeCnt(findNode);
    return ret-1;
}