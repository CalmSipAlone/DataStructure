#include <stdio.h>
#include <string.h>
char ss[10005];
int isd_c (char a,char b){
    if(a>='0'&&a<='9'&&b<='9'&&b>='0'){return 1;}
    else if(a>='A'&&a<='Z'&&b>='A'&&b<='Z'){return 1;}
    else if(a>='a'&&a<='z'&&b>='a'&&b<='z'){return 1;}
    else{return 0;}
}
int main (){
    gets(ss);
    int len = strlen(ss);
    for(int i = 0;i < len;){
        if(ss[i+1] != '-'){printf("%c",ss[i]);i++;}
        else if(ss[i] >= ss[i+2]){
            printf("%c%c",ss[i],ss[i+1]);
            i+=2;
        }
        else if(isd_c(ss[i],ss[i+2]) == 1){
            int num = ss[i+2]- ss[i];
            for(int j = 0;j < num;j++){
                printf("%c",ss[i] + j);
            }
            i += 2;
        }
        else{
            printf("%c%c",ss[i],ss[i+1]);
            i+=2;
        }
    }
    return 0;
}