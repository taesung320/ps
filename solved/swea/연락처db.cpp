//
// Created by 윤태성 on 2022/02/09.
//


#include<cstring>
#include<string>
#include<iostream>
#include<vector>
using namespace std;
typedef struct
{
    int count;
    char str[20];
} RESULT;
typedef enum
{
    NAME,
    NUMBER,
    BIRTHDAY,
    EMAIL,
    MEMO
} FIELD;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct Member{
    string name="";
    string number="";
    string birthday="";
    string email="";
    string memo="";
    bool onMem=true;
    void setField(FIELD fld,string value){
        if(fld==NAME){
            this->name=value;
        } else if (fld == NUMBER) {
            this->number=value;
        } else if (fld == BIRTHDAY) {
            this->birthday=value;
        } else if (fld == EMAIL) {
            this->email=value;
        } else if (fld == MEMO) {
            this->memo=value;
        }
    }
    string getField(FIELD fld){
        if(fld==NAME){
            return this->name;
        } else if (fld == NUMBER) {
            return this->number;
        } else if (fld == BIRTHDAY) {
            return this->birthday;
        } else if (fld == EMAIL) {
            return this->email;
        } else if (fld == MEMO) {
            return this->memo;
        }
    }
};
const int MAX=50001;
const int FIELD_CNT=5;
const unsigned int HASHTABLE=(1<<19);//~500,000
const int DIV=HASHTABLE-1;
typedef unsigned long long ll;
struct HashNode{
    string data="";
    Member* mPtr= nullptr;
    HashNode* next=nullptr;
    HashNode* getPrevNode(string data){
        HashNode* cur=this;
        while ((cur->next!=nullptr)) {
            if(cur->next->data==data) break;
            cur=cur->next;
        }
        return cur;
    }
    void addNode(string data,Member* mPtr){
        HashNode* prev=this->getPrevNode(data);
        HashNode* temp=prev->next;
        HashNode* toAdd=new HashNode();
        toAdd->next=temp;
        toAdd->mPtr=mPtr;
        toAdd->data=data;
        prev->next=toAdd;
    }
};
HashNode hashTable[FIELD_CNT][HASHTABLE]={};
Member buff[MAX];

int buff_cnt;
void InitDB()
{
    buff_cnt=0;
    memset(hashTable, 0, sizeof(hashTable));
}
int getKey(string s){
    ll ret=0;
    for (int i = 0; i < s.size(); ++i) {
        ret +=( ret )+ s[i];
        ret&=DIV;
    }
    return (int)(ret&DIV);
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
    buff[buff_cnt] = Member({name, number, birthday, email, memo,true});
    string temp[5]={name,number,birthday,email,memo};
    for (int i = 0; i < FIELD_CNT; ++i) {
        hashTable[i][getKey(temp[i])].addNode(temp[i],&buff[buff_cnt]);
    }
    buff_cnt++;
}

int Delete(FIELD field, char* str)
{
    HashNode* cur=hashTable[field][getKey(str)].getPrevNode(str);
    int ret=0;
    while(cur->next!=nullptr){
        if(cur->next->data==str&&cur->next->mPtr->onMem){
            //지우고
            HashNode* temp=cur->next;
            temp->mPtr->onMem=false;
            temp->data="";
            cur->next=temp->next;
            ret++;
        }else{
            cur=cur->next;
        }
    }
    return ret;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
    HashNode* cur=hashTable[field][getKey(str)].getPrevNode(str);
    vector<string> toChanges(0);
    int ret=0;
    while(cur!= nullptr&&cur->next!=nullptr){
        if(cur->next->data==str&&cur->next->mPtr->onMem){
            Member* mp=cur->next->mPtr;
            string toChange=mp->getField(changefield);
            if(toChange!=changestr) {
                toChanges.push_back(toChange);
            }
            mp->setField(changefield, changestr);
            if(toChange!=changestr){
                hashTable[changefield][getKey(changestr)].addNode(changestr,mp);
            }
            ret++;
            //
            //
        }
        cur=cur->next;
    }
    for (int i = 0; i < toChanges.size(); ++i) {
        string toChange = toChanges[i];
        HashNode* remover=hashTable[changefield][getKey(toChange)].getPrevNode(toChange);
        if(toChange!=changestr){
            while(remover->next!= nullptr){
                if(remover->next->data==toChange&&(field==changefield||remover->next->mPtr->getField(field)==str)){
                    remover->next->data= "";
                }
                remover=remover->next;
            }
        }
    }
    return ret;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
    RESULT result;
    result.count = 0;
    HashNode* cur=hashTable[field][getKey(str)].getPrevNode(str);
    while(cur!=nullptr){
        if(cur->data==str&&cur->mPtr->onMem){
            Member* mp=cur->mPtr;
            if(result.count==0){
                string temp=mp->getField(ret_field);
                for (int i = 0; i < temp.size(); ++i) {
                    result.str[i]=temp[i];
                }
                result.str[temp.size()]='\0';
            }
            result.count++;
        }
        cur=cur->next;
    }
    return result;
}

//TODO 생각한대로 구현하기는 빨리했으나 세세하게 따져서 사이드 이펙트 또한 발견했어야 했다. .. 모 체인지가 일어났을때 영향받는 내용들 필드가 같을때와 다를때
/**
*
*/