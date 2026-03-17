#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[105];

int main (){
    scanf("%s",s);
    for(int i = 0; i <= strlen(s); i++){
        printf("%c",s[i]);
        if(s[i+1]!='-'){
            ;
        }
        else if((s[i+1] = '-')&&((((s[i]>='A')&&(s[i]<='Z'))&&((s[i+2]>='A')&&(s[i+2]<='Z')))||(((s[i]>='a')&&(s[i]<='z'))&&((s[i+2]>='a')&&(s[i+2]<='z')))||(((s[i]>='0')&&(s[i]<='9'))&&((s[i+2]>='0')&&(s[i+2]<='9'))))){
            for(int j = 1; j < (s[i+2]-s[i]);j++){
                printf("%c",s[i]+j);
            }
            i+=1;
        }
        else{
            i++;
            printf("%c",s[i]);
        }
    }
    return 0;
}