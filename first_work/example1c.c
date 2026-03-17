#include <stdio.h>
#include <string.h>
long long num[100005];
char str[100005];
long long calculator(char s,long long m,long long n){
    if(s == '+'){return (m+n);}
    else {return (m-n);}
}
long long read_read(){
    long long tem;
    scanf("%lld",&tem);
    return tem;
}

int main(){
    num[0] = read_read();
    int i = 0;
    int cnt = 0;
    char ch;
    while(~scanf(" %c",&ch)){
        if((ch == '+')||(ch == '-')){
            str[i] = ch;
            i++;
            cnt++;
            num[cnt] = read_read();
        }
        else if(ch=='*'){
            int tem = read_read();
            num[cnt] *= tem;
        }
        else if(ch == '/'){
            int tem = read_read();
            num[cnt] /= tem;
        }
        else{break;}
    }
    long long re = num[0];
    for(int j = 1; j <= cnt;j++){
            re = calculator(str[j-1],re,num[j]);
    }
    printf("%lld",re);
    return 0;
}