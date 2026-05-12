#include <stdio.h>
#include <string.h>
#include <ctype.h>
char s[55];
char str1[55];
char str2[55];
char ss[26];
int main(){
    gets(s);
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        str1[i] = tolower(s[i]);
    }
    int j = 0;
    for(int i = 0; i < len; i++){
        int cnt = str1[i]-'a';
        if((ss[cnt] == 0)&&(str1[i]>='A'&&str1[i]<='Z'||str1[i]>='a'&&str1[i]<='z')){
            str2[j] = str1[i];
            j++;
            ss[cnt] = 1;
        }
    }
    for(int i = 0;i < 26; i++){
        printf("%c",'a'+i);
    }
    printf("\n");
    for(int x = j-1; x >= 0; x--){
        printf("%c",str2[x]);
    }
    for(int i = 25; i >= 0;i--){
        if(ss[i] == 0){printf("%c",'a'+i);}
    }
}