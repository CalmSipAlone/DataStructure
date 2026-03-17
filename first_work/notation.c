#include <stdio.h>
#include <string.h>
int main (){
    char s[105],re[110];
    gets(s);
    int k;
    if(s[0] != '0'){
    int a;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == '.'){
            a = i;
            break;
        }
    }
        re[0] = s[0];
        re[1] = '.';
        for(int i = 2,j = 1; i < strlen(s); i++,j++){
            if(j == a){
                j++;
            }
            re[i] = s[j];
            k = i;
        }
        re[k+1] = '\0';
        printf("%s",re);
        printf("e");
        printf("%d",a-1);
    }
    else{
        int a;
        for(int i = 2; i < strlen(s); i++){
            if(s[i]!='0'){
                a = i;
                break;
            }
        }
        if(a == (strlen(s)-1)){
            re[0] = s[a];
            re[1] = '\0';
            printf("%s",re);
            printf("e-");
            printf("%d",a-1);
            return 0;
        }
            re[0]  = s[a];
            re[1] = '.';
            for(int i = 2,j = a+1;j <= strlen(s);j++,i++){
                re[i] = s[j];
                k = i;
            }
            re[k+1] = '\0';
            printf("%s",re);
            printf("e-");
            printf("%d",a-1);
    }
    return 0;
}