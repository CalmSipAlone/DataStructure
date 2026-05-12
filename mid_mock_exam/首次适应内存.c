#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int pos;
    int lenth;
    struct node *link;
}Node,*List;

//创建节点
Node* create_node(int pos,int lenth){
    Node *p = (Node*)malloc(sizeof(Node));
    p->pos = pos;
    p->lenth = lenth;
    p->link = NULL;
    return p;
}
//输入形成链表
void input_node(List *head,List *tail){
    int num;
    scanf("%d",&num);
    if(num == 0){
        (*head) = NULL;
        (*tail) = NULL;
        return ;
    }
    while(num--){
        int pos,lenth;
        scanf("%d %d",&pos,&lenth);
        Node *p = create_node(pos,lenth);
        if(*head == NULL){
            *head = p;
        }
        else{
            (*tail)->link = p;
        }
        *tail = p;
    }
    (*tail)->link = *head;
    return ;
}
//空间申请
Node *apply_space_node(List tail){
    if(tail == NULL){return NULL;}
    int l;
    Node *key = tail;
    Node *key_temp = key;
    while(1){
        scanf("%d",&l);
        if(l == -1){break;}
        Node *p = key_temp;
        do{
            if((p->link != NULL)&&(p->link->lenth >= l)){
                key_temp = p;
                break;
            }
            p = p->link;
        }while(p != key);
        key = key_temp;
        if(key == NULL){continue;}

        if(key->link->lenth > l){
            key->link->lenth -= l;
        }
        else if(key->link->lenth == l){
            Node *temp = key->link;
            key->link = key->link->link;
            if(temp == key){
                free(temp);
                return NULL;
            }
            free(temp);
        }
    }
    return key;
}
void free_node(Node *p){
    if(p == NULL) return;

    Node *cur = p->link;
    while(cur != p){
        Node *temp = cur;
        cur = cur->link;
        free(temp);
    }
    free(p);
}
int main(){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    Node *p = apply_space_node(tail);
    Node *k = p;
    if(p == NULL){return 0;}
    do{
        printf("%d %d\n",p->link->pos,p->link->lenth);
        p = p->link;
    }while(p!=k && p != NULL &&(p->link != p));
    free_node(k);
    return 0;
}