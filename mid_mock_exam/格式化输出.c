#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXINT 2147483647
char s[20];
char str[10086];
int main (){
    int m = 0,n = 0,pos = 0;
    gets(s);
    gets(str);
    int len = strlen(s);
    int len1 = strlen(str);
    int op = 0;
    if(s[1] == '-'){op = 1;}
    for(int i = 0; i < len; i++){
        if(s[i] == ':'){pos = i;break;}
    }
    for(int i = 0; i < pos; i++){
        if(s[i]>='0'&&s[i]<='9'){
            m *= 10;
            m += (s[i]-'0');
        }
    }
    for(int i = pos; i < len; i++){
        if(s[i]>='0'&&s[i]<='9'){
            n *= 10;
            n += (s[i]-'0');
        }
    }

    if(n<=m&&m<=len1){
        str[m] = '\0';
        printf("%s",str);
    }
    else if(n<=len1&&m>len1){printf("%s",str);}
    else if(n>m&&m<=len1){
        str[m] = '\0';
        if(op==0){
            printf("%s",str);
            for(int i = 1; i <= n-m; i++){
                printf("#");
            }
        }
        else{
            for(int i = 1; i <= n-m; i++){
                printf("#");
            }
            printf("%s",str);
        }
    }
    else if(n>len1&&m>len1){
        if(op==0){
            printf("%s",str);
            for(int i = 1; i <= n-len1; i++){
                printf("#");
            }
        }
        else{
            for(int i = 1; i <= n-len1; i++){
                printf("#");
            }
            printf("%s",str);
        }
    }
    return 0;
}