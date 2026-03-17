#include <stdio.h>
#include <string.h>
void func (char *q){
    char a[] = "hello";
    strcpy(q,a);
}
int index(char s[],char t[])
{
 int i,j,k;
 for(i=0;s[i]!='\0';i++)
 {
  for(j=i,k=0;&&s[j]==t[k];j++,k++)
   ;
  if()
   return i;
 }
 return -1;
}


int main(){
    char str[20];
    char *p = str;
    func(p);
    printf("%s",p);
    return 0;
}