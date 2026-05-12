#include <stdio.h>
#include <stdlib.h>
struct node {
        int n;
        struct node *link;
};

int main()
{
    int n;
    struct node *list=NULL, *q;

    scanf("%d",&n);
    while(n!=-1){
        q = (struct node *) malloc(sizeof(struct node));
        q->n = n;
        q->link = NULL;
        if(list == NULL){
            list = q;
        }
        else{
            q->link = list;
        }
        list = q;
        scanf("%d",&n);
    }
    
    while(list!=NULL){
        q=list;
        printf("%d ",list->n);
        list=list->link;
        free(q); 
    }

    return 0;
} 
