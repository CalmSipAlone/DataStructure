#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[55];
    char author[25];
    char publisher[35];
    char date[12];
} books;

int compare_books (const void *a, const void *b);
void insert_books(books array[],int *num,books new_book);
void search_books(const char *key_words,int *num);
void delete_books (const char *keywords,int *num);

books array[505];

int main(){
    int num = 0;
    FILE *in,*out;
    in = fopen("books.txt","r");
    while(fscanf(in,"%s %s %s %s",array[num].name,array[num].author,array[num].publisher,array[num].date)!=EOF){
        num++;
        if(num>=501){
            printf("ERROR");
            break;
        }
    }
    fclose(in);
    qsort(array,num,sizeof(books),compare_books);
    int op;
    while(1){
        scanf("%d",&op);
        if(op == 1){
        books new_book;
        scanf("%s %s %s %s",new_book.name,new_book.author,new_book.publisher,new_book.date);
        insert_books(array,&num,new_book);
    }
    else if(op == 2){
        char *key_words;
        char tem[55];
        scanf("%s",tem);
        key_words = tem;
        search_books(key_words,&num);
    }
    else if(op == 3){
        char *keywords;
        char tem[55];
        scanf("%s",tem);
        keywords = tem;
        delete_books(keywords,&num);
    }
    else {
        break;
    }
}
        out = fopen("ordered.txt","w");
        for(int i = 0; i < num; i++){
            fprintf(out,"%-50s%-20s%-30s%-10s\n",array[i].name,array[i].author,array[i].publisher,array[i].date);
        }
        fclose(out);
        return 0;
    
}
//qsort排序函数
int compare_books (const void *a, const void *b){
    books *bookA = (books *)a;
    books *bookB = (books *)b;
    return strcmp(bookA->name, bookB->name);
}
//录入书籍函数
void insert_books(books array[],int *num,books new_book){
    array[*num] = new_book;
    (*num)++;
    qsort(array,*num,sizeof(books),compare_books);
}
//查找关键字函数
void search_books(const char *key_words,int *num){
    int flag = 0;
    for(int i = 0; i < *num; i++){
        if(strstr(array[i].name,key_words) != NULL){
            printf("%-50s%-20s%-30s%-10s\n",array[i].name,array[i].author,array[i].publisher,array[i].date);
            flag = 1;
        }
    }
    if(flag == 0){printf("未找到相关书籍！");}
}
//删除书籍函数
void delete_books (const char *keywords,int *num){
    int i = 0;
    while(i < *num){
        if(strstr(array[i].name,keywords) != NULL){
            for(int j = i; j < (*num)-1; j++){
                array[j] = array[j+1];
            }
            (*num)--;
        }
        else{
            i++;
        }
    }
}
