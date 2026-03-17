#include <stdio.h>
#include <string.h>
char num[2][85] = {0};
int nums[3][85] = {0};
int main(){
    int len1 = 0, len2 = 0, len3 = 0,flag = 0; 
    scanf("%s",num[0]);
    scanf("%s",num[1]); 
    len1 = strlen(num[0]);
    len2 = strlen(num[1]);
    int max = len1 > len2 ? len1 : len2; 
    for (int i = 0; i < len1; i++){
        nums[0][i] = num[0][len1 - i- 1]-'0';
    }
    for (int i = 0; i < len2; i++){
        nums[1][i] = num[1][len2 - i- 1]-'0';
    }

    if(len1 < len2){
        flag = 1;
    }
    else if (len1 == len2){
        for(int i = len1-1;i>=0;i--){
            if(nums[0][i]<nums[1][i]){
                flag = 1;
                break;
            }
            else if(nums[0][i]>nums[1][i]){
                break;
            }
        }
    }
    if(flag == 0){
        for(int i = 0; i < len1;i++){
            nums[2][i] = nums[0][i]-nums[1][i];
            if(nums[2][i]<0){
                nums[2][i]+=10;
                nums[0][i+1]--;
            }
        }
    }
    else{
        for(int i = 0; i < len2;i++){
            nums[2][i] = nums[1][i]-nums[0][i];
            if(nums[2][i]<0){
                nums[2][i]+=10;
                nums[1][i+1]--;
            }
        }
        printf("-");
    }
    len3 = max;
    while((nums[2][len3]==0)&&(len3>0)){
        len3--;
    }
    for (int i = len3; i >= 0; i--) {
        printf("%d",nums[2][i]);
    }
        
    return 0;
}