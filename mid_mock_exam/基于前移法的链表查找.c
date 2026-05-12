#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int num;
    int cnt;
    struct node *link;
}Node,*List;
int count = 0;
//创建节点
Node* create_node(int num){
    Node *p = (Node*)malloc(sizeof(Node));
    p->num = num;
    p->cnt = 1;
    p->link = NULL;
    return p;
}
//输入形成链表
void input_node(List *head,List *tail){
    int num;
    scanf("%d",&num);
    while(num--){
        int x;
        scanf("%d",&x);
        Node *p = create_node(x);
        if( *head == NULL){
            (*head) = p;
            (*tail) = p;
        }
        else{
            Node (*q) = (*head);
            count++;
            if(q->num == p->num){
                (q->cnt)++;
                free(p);
                continue;
            }
            int flag = 0;
            while(q->link != NULL){
                count++;
                if(q->link->num == p->num){
                    p->cnt = (q->link->cnt)+1;
                    flag = 1;
                    Node *temp = q->link;
                    q->link = q->link->link;
                    free(temp);
                    p->link = (*head);
                    (*head) = p;
                    break;
                }
                else{q = q->link;}
            }
            if(flag == 0){
                (*tail)->link = p;
                (*tail) = p;
            }
        }
    }
}
int main (){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    Node *p = head;
    printf("%d\n",count);
    int cntt = 0;
    while(p != NULL){
        if(cntt == 5){break;}
        printf("%d %d\n",p->num,p->cnt);
        cntt++;
        p = p->link;
    }
    return 0;
}