#include <stdio.h>
#include <string.h>
char str[105];
int main() {
    gets(str);
    int len = strlen(str);
    int point;
    int zero=-1;
    int f_zero;
    for(int i = 0; i < len; i++){
        if(str[i] == '.'){point = i;}
        else if(str[i] != '0'){
            if(zero == -1){f_zero = i;}
            zero = i;
        }
    }
    if(str[0] != '0'){
        printf("%c.",str[0]);
        for(int i = 1; i <= zero; i++){
            if(str[i] == '.'){continue;}
            else{
                printf("%c",str[i]);
            }
        }
        printf("e%d",point-1);
    }
    else{
        if(f_zero == len-1){printf("%c",str[f_zero]);}
        else{printf("%c.",str[f_zero]);}
        for(int i = f_zero+1; i <= zero; i++){
            printf("%c",str[i]);
        }
        printf("e-");
        printf("%d",f_zero-1);
    }
    return 0;
}