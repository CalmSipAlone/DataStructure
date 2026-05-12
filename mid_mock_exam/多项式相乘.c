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
void input_node (List* head,List* tail){
    char c;
    do{
        int a,x;
        scanf("%d%d%c",&a,&x,&c);
        Node *p = create_node(a,x);
        if(*head == NULL){
            *head = p;
        }
        else{
            (*tail)->link = p;
        }
        *tail = p;
    }while(c != '\n');
}
Node*  multi_node(List L1,List L2){
    Node *head = NULL,*tail = NULL;
    Node *p = L1;
    Node *q = L2;
    Node *r = NULL;
    while(p != NULL){
        while(q != NULL){
            int a = (p->a)*(q->a);
            int x = (p->x)+(q->x);
            r = create_node(a,x);
            if(head == NULL){
                head = r;
            }
            else{
                tail->link = r;
            }
            tail = r;
            q = q->link;
        }
        q = L2;
        p = p->link;
    }
    return head;
}
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
void desame_node(List head){
    Node *p = head;
    while(p != NULL){
        Node *q = p->link;
        if(q == NULL){break;}
        if(p->x == q->x){
            p->a += (q->a);
            Node *temp = q;
            p->link = p->link->link;
            free(temp);
        }
        else {p = p->link;}
    }
}
void print_node(Node *head){
    Node *p = head;
    while(p!= NULL){
        printf("%d %d ",p->a,p->x);
        p = p->link;
    }
    return ;
}
int main (){
    Node *L1 = NULL,*L2 = NULL,*L3 = NULL;
    Node *T1 = NULL,*T2 = NULL;
    input_node(&L1,&T1);
    input_node(&L2,&T2);
    L3 = multi_node(L1,L2);
    L3 = sort_node(L3);
    desame_node(L3);
    L3 = sort_node(L3);
    print_node(L3);
    return 0;
}