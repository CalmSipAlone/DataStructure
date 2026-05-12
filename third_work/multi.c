#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int a;
    int x;
    struct Node *link;
}Node,*List;
Node* create_node(int a,int x){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->a = a;
    newnode->x = x;
    newnode->link = NULL;
    return newnode;
}
//创建节点
void input_node(List *head,List *tail){
    int aa,xx;
    char ch;
    do{
        scanf("%d%d%c",&aa,&xx,&ch);
        Node *p=create_node(aa,xx);
        if(*head==NULL){
            *head = p;
        }
        else{
            (*tail)->link = p;
        }
        *tail = p;
    }while(ch != '\n');
}
//输入
void mergesame_node(List head){
    if(head == NULL){return;}
    Node *p = head;
    while(p!=NULL){
        Node *n = p;
        while(n->link != NULL){
            if(p->x == n->link->x){
                (p->a) +=(n->link->a);
                Node *temp = n->link;
                n->link = n->link->link;
                free(temp);
            }
            else{
                n = n->link;
            }
        }
        p = p->link;
    }
}
//合并同类项
Node* sort_node(Node *head){
    if (head == NULL || head->link == NULL) {return head;}
    Node *sorted = NULL, *curr = head, *next;
    while (curr != NULL) {
        next = curr->link;
        if (sorted == NULL || curr->x > sorted->x) {
            curr->link = sorted;
            sorted = curr;
        }
        else {
            Node *p = sorted;
            while (p->link != NULL && p->link->x > curr->x) {
                p = p->link;
            }
            curr->link = p->link;
            p->link = curr;
        }
        curr = next;
    }
    return sorted;
}
//插入排序
void free_node(List head){
    Node *p = head;
    while(p != NULL){
        Node *temp = p;
        p = p->link;
        free(temp);
    }
}
//释放
void print_node(List head){
    Node *p = head;
    if(p == NULL){
        printf("0");
    }
    while(p != NULL){
        printf("%d %d ", p->a,p->x);
        Node *temp = p;
        p = p->link;
        free(temp);
    }
}
//打印
Node* multiply_node(List L1,List L2){
    Node *L3 = NULL,*tail = NULL;
    Node *p1 = L1,*p2;
    while(p1 != NULL){
        p2 = L2;
        while(p2!=NULL){
            int a = (p1->a)*(p2->a);
            int x = (p1->x) + (p2->x);
            Node *q = create_node(a,x);
            if(L3 == NULL){
                L3 = q;
            }
            else{
                tail->link = q;
            }
            tail = q;
            p2 = p2->link;
            }
        p1 = p1->link;
    }
    return L3;
}
//相乘
int main (){
    Node *L1=NULL, *tail1=NULL, *L2=NULL, *tail2=NULL, *L3=NULL;
    input_node(&L1,&tail1);
    input_node(&L2,&tail2);
    L3 = multiply_node(L1,L2);
    mergesame_node(L3);
    L3 = sort_node(L3);
    print_node(L3);
    return 0;
}