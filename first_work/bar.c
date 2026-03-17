#include <stdio.h>
#include <string.h>
char s[1000000],str[1000005];
int num[26];
int max(int a[],int m);
int main (){
    while(gets(str)!=NULL){
        strcat(s,str);
    }
    for(int i = 0; i <= strlen(s);i++){
        if((s[i]>='a')&&(s[i]<='z')){
            num[(s[i]-'a')]++;
        }
    }
    int c = max(num,26);
    while(c!=0)
    {for(int i = 0; i < 26; i++){
        if(num[i] < c){
            printf(" ");
        }
        else{
            printf("*");
            num[i]--;
        }
    }
    printf("\n");
    c--;
    }
    for(int i = 0; i < 26; i++){
        printf("%c",i+'a');
    }
return 0;
}

int max(int a[],int m){
    int max = 0;
    for(int i = 0; i < m; i++){
        if(max <= a[i]){
            max = a[i];
        }
    }
    return max;
}