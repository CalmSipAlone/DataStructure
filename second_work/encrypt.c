#include <stdio.h>
#include <string.h>
char str[10086];
char S[10000005];
char temp[10000005];
int main (){
    char s[26];
    char ss[26];
    int num[26] = {0};
    for(int i = 0; i < 26; i++){
        s[i] = 'a' + i;
    }
    gets (str);
    int x = 0;
    for (int i = 0; i < strlen(str);i++){
        int a = str[i] - 'a';
        num[a]++;
        if(num[a] == 1){
            ss[x] = str[i];
            x++;
        }
    }
    for(int i = 25; i >= 0; i--){
        if(num[i] == 0){
            ss[x] = s[i];
            x++;
        }
    }


    FILE *in, *out;
    in = fopen("encrypt.txt","r");
    out = fopen("output.txt","w");

    if((in == NULL)||(out == NULL)){
        printf("打开文件失败");
        return 1;
    }
    int y = 0;
    while ((temp[y] = fgetc(in)) != EOF){
        if((temp[y]>='a')&&(temp[y] <= 'z')){
            int aa = temp[y] - 'a';
            S[y] = ss[aa];
        }
        else{
            S[y] = temp[y];
        }
        y++;
    }
    for(int i = 0; i <= y; i++){
        fputc(S[i],out);
    }
    fclose(in);
    fclose(out);
    return 0;
}