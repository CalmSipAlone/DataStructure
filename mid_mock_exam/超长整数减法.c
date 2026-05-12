#include <stdio.h>
#include <string.h>
char a[1005],b[1005];
int c[1005];
char aa[1005] ,bb[1005];
int cmp(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a != len_b) {
        return len_a > len_b ? 1 : -1;
    }
    // 长度相等：从高位开始逐位比较（核心修复！）
    return strcmp(a, b);
}
int main (){
    gets(a);
    gets(b);
    int len1 = strlen(a),len2 = strlen(b);

    int flag = cmp(a,b);
    for(int i = 1004; i >= 0;i--){
        aa[i] = '0';
        bb[i] = '0';
    }
    for(int i = len1-1,j = 0;i>=0;i--,j++){
        aa[j] = a[i];
    }
    for(int i = len2-1,j = 0;i>=0;i--,j++){
        bb[j] = b[i];
    }

    if(flag == 1||flag == 0){
        int i = 0;
        while(i <= len1-1){
            c[i] += (int)(aa[i]-bb[i]);
            if(c[i] < 0){
                c[i] += 10;
                c[i+1]--;
            }
            i++;
        }
        int ff = 0;
        for(int i = len1-1; i >= 0; i--){
            if(c[i] != 0){ff = 1;}
            if(ff == 1){
                printf("%d",c[i]);
            }
        }
        if(ff == 0){printf("0");}
    }
    else{
        int i = 0;
        while(i <= len2-1){
            c[i] += (int)(bb[i]-aa[i]);
            if(c[i] < 0){
                c[i] += 10;
                c[i+1]--;
            }
            i++;
        }
        int ff = 0;
        printf("-");
        for(int i = len2-1; i >= 0; i--){
            if(c[i] != 0){ff = 1;}
            if(ff == 1){
                printf("%d",c[i]);
            }
        }
    }
    return 0;
}