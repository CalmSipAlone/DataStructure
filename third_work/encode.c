#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char ch;
    struct Node *link;
}Node,*List;
Node* create_node(char ch){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->ch = ch;
    newnode->link = NULL;
    return newnode;
}
//去重
void desame(char *key,char *new_key){
    int count = 0;
    for(int i = 0; key[i] != '\0'; i++){
        int flag = 0;
        char c = key[i];
        for(int j = 0; j < count; j++){
            if(new_key[j] == key[i]){flag = 1;}
        }
        if(flag == 0){
            new_key[count] = c;
            count++;
        }
    }
    new_key[count] = '\0';
}
//生成字符串
void create_string(char *new_key,char *string_key){
    int count = 0;
    for(int i = 0; new_key[i] != '\0';i++){
        string_key[count++] = new_key[i];
    }
    for(int i = 32; i < 127;i++){
        int flag = 0;
        for(int j = 0 ;j < count; j++){
            if((char)i == string_key[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            string_key[count] = (char)i;
            count++;
        }
    }
    string_key[count] = '\0';
}
//输入形成链表
void input_node(List *head,List *tail,char *string_key){
    for(int i = 0; string_key[i] != '\0';i++){
        Node *p = create_node(string_key[i]);
        if(*head == NULL){
            (*head) = p;
        }
        else{
            (*tail)->link = p; 
        }
        (*tail) = p;
    }
    (*tail)->link = (*head);
    return;
}
//形成加密表
void map(List head,char c,char map[127]){
    if (head == NULL) return;
    Node *pre = head;
    while (pre->link != head) {
        pre = pre->link;
    }
    Node *p = head;
    int total = 95;
    while (total > 1) {
        char ch = p->ch;
        pre->link = p->link;
        Node *next = p->link;
        free(p);
        total--;
        int step = (int)ch % total;
        if (step == 0) step = total;
        Node *q = next;
        for (int i = 1; i < step; i++) {
            q = q->link;
        }
        map[(int)ch] = q->ch;
        p = q;
        pre = p;
        while (pre->link != p) {
            pre = pre->link;
        }
    }
    map[(int)(p->ch)] = c;
}
int main (){
    char ss[33] = {0};
    gets(ss);
    char new_key[33] = {0};
    desame(ss,new_key);
    char c = new_key[0];
    char string_key[100] = {0};
    create_string(new_key,string_key);
    Node *head = NULL,*tail = NULL;
    input_node(&head,&tail,string_key);
    char mapp[127] = {0};
    map(head,c,mapp);
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("in_crpyt.txt", "w");
    if (!in || !out) {
        printf("文件打开失败\n");
        return 1;
    }
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch >= 32 && ch <= 126) {
            fputc(mapp[ch], out);
        } else {
            fputc(ch, out);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}