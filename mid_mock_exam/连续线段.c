#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int x1;
    int y1;
    int x2;
    int y2;
    struct node *next;
}Node, *List;
Node* create_node(int x1,int y1,int x2,int y2){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->x1 = x1;
    newnode->y1 = y1;
    newnode->x2 = x2;
    newnode->y2 = y2;
    newnode ->next = NULL;
    return newnode;
}
void input_node(List* head,List* tail){
    int total;
    scanf("%d",&total);
    while(total--){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        Node *p = create_node(x1,y1,x2,y2);
        if(*head == NULL){
            *head = p;
        }
        else{
            (*tail)->next = p;
        }
        (*tail) = p;
    }
}
int cmp(Node *p,Node*q){
    if((p->x2 == q->x1)&&(p->y2 == q->y1)){return 1;}
    else{return 0;}
}
int main (){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    Node *p  = head;
    int cnt = 1;
    int max = 0;
    Node *key = NULL;
    while(p != NULL){
        Node *q = head;
        Node *temp = p;
        while(q != NULL){
            if(cmp(temp,q) == 1){
                cnt++;
                temp = q;
                q = head;
            }
            else{q = q->next;}
        }
        if(max < cnt){
            max = cnt;
            key = p;
        }
        cnt = 1;
        p = p->next;
    }
    printf("%d %d %d",max,key->x1,key->y1);
    return 0;
}