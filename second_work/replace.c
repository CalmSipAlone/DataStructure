#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main (){
    char s[10086];
    char t[10086];
    char ss[10086];
    char str[1000005];
    char sstr[1000005];
    gets(s);
    gets(t);
    int len1 = strlen(s);
    int len2 = strlen(t);
    for(int x = 0; x < len1; x++){
        ss[x] = tolower(s[x]);
    }
    FILE *in,*out;
    in = fopen("filein.txt","r");
    out = fopen("fileout.txt","w");
    if((in == NULL)||(out == NULL)){
        printf("打开文件失败");
        return 1;
    }
    int i = 0, j = 0, m = 0;
    while((str[i] = fgetc(in) )!= EOF){
        sstr[i] = tolower(str[i]);
        i++;
    }
    
    for(m = 0,j = 0; m < i; m++){
        if(ss[j] == sstr[m]){
            j++;
            if(j == len1){
                for(int x = 0; x < len2; x++){
                    fputc(t[x],out);
                }
                j = 0;
            }
        }
        else{
            if(j == 0){
                fputc(str[m],out);
            }
            else{
                for(int x = j ;x >= 0; x--){
                    fputc(str[m-x],out);
                }
                j = 0;
            }
        }
    }
    fclose(in);
    fclose(out);
    return 0;

}