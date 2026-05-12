#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char str[10005];
char s[55][35];
int lines[55];
int cmp(const void *e1, const void *e2){
    int i = *((int *) e1), j = *((int *) e2);//get line number
    if (strcmp(s[i], s[j]) > 0)
    return 1;
    if (strcmp(s[i], s[j]) < 0)
    return -1;
    return 0;
}
int main (){
    gets(str);
    int len = strlen(str);
    int j = 0,k = 0,i = 0;
    while(i != len){
        char ch = str[i];
        if(((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'))||((ch>='0')&&(ch<='9'))||ch =='_'){
            s[j][k] = ch;
            k++;
            i++;
        }
        else{
            lines[j] = j;
            j++;
            k = 0;
            i++;
        }
    }
    qsort(lines,j,sizeof(int),cmp);
    int m = 0;
    for(m = 0; m < j; m++){
        char ch = s[lines[m]][0];
        int flag = 0;
        for(int n = 0; n < m; n++){
            if(strcmp(s[lines[n]],s[lines[m]])==0){
                flag = 1;
                break;
            }
        }
        if((flag == 0)&&(((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'))||ch =='_')){
            printf("%s ",s[lines[m]]);
        }
    }
    return 0;
}
