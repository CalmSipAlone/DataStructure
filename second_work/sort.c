#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[25];
    long long tel;
    int key;
}Information;
Information member[101];
int falg = 0;
void SortByname(Information member[],int num);
int main (){
    int num;
    scanf ("%d",&num);//输入读取电话号码的个数

    for(int i = 0; i < num; i++){
        scanf("%s %lld",member[i].name,&member[i].tel);//输入姓名和电话
        member[i].key = 0;
    }
    SortByname(member,num);
    return 0;
}

void SortByname(Information member[],int num){
    int i,j;
    Information temp;
    for(i = 0; i < num;i++){
        for(j = i; j < num-1; j++){
            if((strcmp(member[i].name,member[j+1].name) == 0)&&(member[i].tel == member[j+1].tel)){
                for(int k = j+1;k < num-1;k++){
                    member[k] = member[k+1];
                }
                num--;
            }
            else if(strcmp(member[i].name,member[j+1].name) == 0){
                member[i].key++;
                char tem[10];
                sprintf(tem,"_%d",member[i].key);
                strcat(member[j+1].name,tem);
            }
            if(strcmp(member[i].name , member[j+1].name) > 0){
                temp = member[i];
                member[i] = member[j+1];
                member[j+1] = temp;
            }
        }
    }
    for(int i = 0; i < num; i++){
        printf("\n%s %lld\n",member[i].name,member[i].tel);
    }
}