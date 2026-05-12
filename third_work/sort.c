#include <stdio.h>
#include <stdlib.h>
#define MAXINT 2147483647
typedef struct node{
    int num;
    struct node *pre;
    struct node *next;
}Node,*List;
int tot;
//创建节点
Node* create_node(int num){
    Node *p = (Node*)malloc(sizeof(Node));
    p->num = num;
    p->pre = NULL;
    p->next = NULL;
    return p;
}
void input_node (List *head,List* tail){
    int total;
    scanf("%d",&total);
    tot = total;
    while(total--){
        int num;
        scanf("%d",&num);
        Node *p = create_node(num);
        if(*head == NULL){
            *head = p;
            *tail = p;
        }
        else{
            p->pre = (*tail);
            (*tail)->next = p;
            (*tail) = p;
        }
    }
    (*head)->pre = (*tail);
    (*tail)->next = (*head);
}
int main (){
    Node *head = NULL;
    Node *tail = NULL;
    input_node(&head,&tail);
    Node *start = head;
    while(tot>0){
        Node *now = start;
        Node *p = start;
        Node *key = NULL;
        int min = MAXINT;
        do{
            if(now->num < min){
                key = now;
                min = (now->num);
            }
            now = now->next;
        }while(now != start);
        do{
            printf("%d ",p->num);
            p = p->next;
        }while(p != key->next);
        start = key->next;
        Node *temp = key;
        key->pre->next = key->next;
        key->next->pre = key->pre;
        free(temp);
        tot--;
        printf("\n");
    }
    return 0;
}