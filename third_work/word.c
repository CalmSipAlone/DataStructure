#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char ss[1000005];
char s[30];
typedef struct node{
    char keywords[25];
    int count;
    struct node *link;
}Node,*List;

Node* create_node(char ch[25]){
    Node *newnode = (Node*)malloc(sizeof(Node));
    if(newnode == NULL){
        exit(1);
    }
    strcpy(newnode->keywords, ch);
    newnode->count = 1;
    newnode->link = NULL;
    return newnode;
}

void input_node(List *head,List *tail){
    FILE *in = fopen("article.txt", "r");
    if (!in) {
        printf("文件打开失败\n");
        return ;
    }
    int ch;
    int i = 0;
    while ((ch = fgetc(in)) != EOF && i < 1000000) {
        ss[i] = tolower(ch);
        i++;
    }
    int x = 0;
    for(int j = 0;j < i;j++){
        if(isalpha(ss[j])){
            s[x] = ss[j];
            x++;
        }
        else{
            if(x > 0){
                s[x] = '\0';
                Node *p = create_node(s);
                if(*head == NULL){
                    (*head) = p;
                    *tail = p;
                }
                else{
                    Node *q = (*head);
                    int flag = 0;
                    while(q != NULL){
                        if(strcmp(q->keywords,p->keywords) == 0){
                            (q->count)++;
                            flag = 1;
                            free(p);
                            break;
                        }
                        q = q->link;
                    }
                    if(flag == 0){
                        (*tail) ->link = p;
                        *tail = p;
                    }
                }
                memset(s, 0, sizeof(s));
                x = 0;
            }
        }
    }
    if(x > 0){
        s[x] = '\0';
        Node *p = create_node(s);
        Node *q = *head;
        int flag = 0;
        while(q != NULL){
            if(strcmp(q->keywords,p->keywords) == 0){
                q->count++;
                flag = 1;
                free(p);
                break;
            }
            q = q->link;
        }
        if(flag == 0){
            (*tail)->link = p;
            *tail = p;
        }
    }
    fclose(in);
    return;
}

Node* sort_node(Node *head){
    if (head == NULL || head->link == NULL) {return head;}
    Node *sorted = NULL, *curr = head, *next;
    while (curr != NULL) {
        next = curr->link;
        if (sorted == NULL || strcmp(curr->keywords,sorted->keywords)<0) {
            curr->link = sorted;
            sorted = curr;
        }
        else {
            Node *p = sorted;
            while (p->link != NULL && strcmp(p->link->keywords,curr->keywords)<0) {
                p = p->link;
            }
            curr->link = p->link;
            p->link = curr;
        }
        curr = next;
    }
    return sorted;
}

int main (){
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail);
    head = sort_node(head);
    Node *p = head;
    while(p != NULL){
        printf("%s %d\n",p->keywords,p->count);
        Node *temp = p;
        p = p->link;
        free(temp);
    }
    return 0;
}