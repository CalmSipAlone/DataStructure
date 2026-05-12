#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int x1,y1,x2,y2;
    struct node *link;
}Node,*List;
//创建节点
Node* create_node(int x1,int y1,int x2,int y2){
    Node *p = (Node*)malloc(sizeof(Node));
    p->x1 = x1;
    p->y1 = y1;
    p->x2 = x2;
    p->y2 = y2;
    p->link = NULL;
    return p;
}
//判断是否在一条线上
int is_point(List a,List b){
    if((a->x2 == b->x1)&&(a->y2 == b->y1)){return 1;}
    else{return 0;}
}
//输入形成链表
void input_node(List *head,List *tail){
    int num;
    scanf("%d",&num);
    while(num--){
        int x1,x2,y1,y2;
        scanf(" %d%d%d%d",&x1,&y1,&x2,&y2);
        Node *p = create_node(x1,y1,x2,y2);
        if(*head == NULL){
            *head = p;
            *tail = p;
        }
        else{
                (*tail) ->link = p;
                (*tail) = p;
        }
    } 
    return;
}

int main (){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    Node *p = head;
    int max = 0;
    Node *start = NULL;
    while(p != NULL){
        int cnt = 1;
        Node *now = p;
        while(1){
            Node *next = NULL;
            Node *temp = head;
            while(temp != NULL){
                if(is_point(now,temp) == 1){
                    next = temp;
                    break;
                }
                temp = temp->link;
            }
            if(next != NULL){
                cnt++;
                now = next;
                continue;
            }
            else{
                break;
            }
        }
        if(cnt > max){
            start = p;
            max = cnt;
        }
        p = p->link;
    }
    printf("%d %d %d",max,start->x1,start->y1);
    return 0;
}