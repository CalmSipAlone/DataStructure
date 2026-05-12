#include <stdio.h>
#include <stdlib.h>
struct node {
        int n;
        struct node *link;
};
int main()
{
    int n;
    struct node *list=NULL, *tail, *q;
    
    scanf("%d",&n);
    while(n!=-1){
        q = (struct node *)malloc(sizeof(struct node));
        q->n = n; 
        q->link = NULL;
        
        if(list == NULL)
            list = q;
        else 
            tail->link = q;
        tail=q;
        
        scanf("%d",&n);
    }
    struct node *p = list;
    while(p != NULL){
    int num = p->n;
    int len;
    char s[50];
    for(int i = 1; i < 50; i++){
        if((i % 4) != 0){
            s[i] = (num%10) + '0';
            num /= 10;
        }
        else{
            s[i] = ',';
        }
        if(num == 0){
            len = i;
            break;
        }
    }
    for(int j = len; j > 0; j--){
        printf("%c",s[j]);
    }
        printf(" ");
        struct node *temp = p;
        p = p -> link;
        free(temp);
    }
    return 0;
}
