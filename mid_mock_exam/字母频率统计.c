#include <stdio.h>
#include <ctype.h>
#include <string.h>
char s[1000005];
char ss[10000005];
int count[26];
int main (){
    int i = 0;
    while(gets(ss) != NULL){
        strcat(s,ss);
    }
    int len = strlen(s);
    do{
        char tem;
        tem = s[i];
        int cnt = (tem -'a');
        if(cnt>=0 && cnt<=25){count[cnt]++;}
        i++;
    }while(i!=len);
    int max = 0;
    for(int j = 0; j < 26; j++){
        if(count[j] > max){
            max = count[j];
        }
    }
    while(max > 0){

        for(int i = 0; i < 26; i++){
            if(count[i] < max){printf(" ");}
            else{
                printf("*");
                count[i]--;
            }
        }
        max--;
        printf("\n");
    }
    for(int i = 0; i < 26; i++){
        printf("%c",'a'+i);
    }
    return 0;
}