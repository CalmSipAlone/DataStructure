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
        q->link = list;
        if(list==NULL) 
            list=q;
        else
            tail->link=q;
        tail=q;                
        scanf("%d",&n);
    }
    tail->link = list;
    struct node *p = list;
    struct node *pre = tail;
    while(pre->link != pre){
        printf("%d ", p->n);
        struct node *temp = p;
        pre->link = p->link;
        pre = pre->link;
        p = pre->link;
        free(temp);
    }
    printf("%d ",p->n);
    free(p);

    return 0;
} 