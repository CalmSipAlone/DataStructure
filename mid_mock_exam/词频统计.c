#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXINT 2147483647
int len = 0;
char str[105];
char s[1000005];
typedef struct node{
    char s[105];
    int cnt;
    struct node *rnode;
}Node,*List;
Node *create_node(char str[]){
    Node *newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->s,str);
    newnode->cnt = 1;
    newnode->rnode = NULL;
    return newnode;
}
void input_node(List *head,List *tail){
    int ch;
    while((ch = getchar())!= EOF){
        s[len++] = tolower(ch);
    }
    int i = 0,cnt = 0;;
    while(1){
        if(s[i] >= 'a'&&s[i] <= 'z'){
            str[cnt++] = s[i++];
        }
        else{
            Node *p = create_node(str);
            if(*head == NULL){
                *head = p;
                *tail = p;
            }
            else{
                Node *q = *head;
                int flag = 0;
                while(q != NULL){
                    if(strcmp(p->s,q->s) == 0){
                        (q->cnt)++;
                        flag = 1;
                        break;
                    }
                    q = q->rnode;
                }
                if(flag == 0){
                    (*tail)->rnode = p;
                    (*tail) = p;
                }
            }
        }
    }
}