#include <stdio.h>
#include <stdlib.h>
#define MAXINT 2147483647
typedef struct node{
    int pos;
    int lenth;
    struct node *lnode;
    struct node *rnode;
}Node,*List;
Node *create_node(int pos,int lenth){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->pos = pos;
    newnode->lenth = lenth;
    newnode->lnode = NULL;
    newnode->rnode = NULL;
    return newnode;
}
void input_node(List *head,List *tail){
    int num;
    scanf("%d",&num);
    while(num--){
        int pos,lenth;
        scanf("%d%d",&pos,&lenth);
        Node *p = create_node(pos,lenth);
        if(*head == NULL){
            *head = p;
        }
        else{
            p->lnode = *tail;
            (*tail)->rnode = p;
        }
        *tail = p;
    }
    (*head)->lnode = *tail;
    (*tail)->rnode = *head;
}
int main (){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    Node *now = head;

    while(1){
        Node *goal = NULL;
        int min = MAXINT;
        int len;
        scanf("%d",&len);
        if(len == -1){break;}
        Node *p = now;
        do{
            if(((p->lenth) >= len)&&((p->lenth) < min)){
                min = (p->lenth);
                goal = p;
            }
            p = p->rnode;
        }while(p!=now);
        if(goal == NULL){continue;}
        else if(len == min){
            Node *temp = goal;
            if(goal->rnode == goal){free(goal);return 0;}
            else{
                goal->lnode->rnode = goal->rnode;
                goal->rnode->lnode = goal->lnode;
                now = goal->rnode;
                free(temp);
            }
            
        }
        else{
            (goal->lenth) -= len;
            now = goal;
        }
    }

    Node *p = now;
    if(p == NULL){return 0;}
    else{
        do{
            printf("%d %d\n",p->pos,p->lenth);
            p = p->rnode;
        }while(p!= now);
    }
    return 0;
}