#include <stdio.h>
int board[19][19];
int main (){
    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            scanf("%d",&board[i][j]);
        }
    }
    int cnt = 0;
    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            if((board[i][j] == 1)&&(((board[i][j+1] == 1)&&(board[i][j+2] == 1)&&(board[i][j+3] == 1)&&(j<15)&&((board[i][j+4] == 0)||(board[i][j-1] == 0)))||((i<15)&&(board[i+1][j] == 1)&&(board[i+2][j] == 1)&&(board[i+3][j] == 1)&&((board[i+4][j] == 0)||(board[i-1][j] == 0)))||(((i<15)&&(j<15))&&(board[i+1][j+1] == 1)&&(board[i+2][j+2] == 1)&&(board[i+3][j+3] == 1)&&((board[i+4][j+4] == 0)||(board[i-1][j-1] == 0)))||(((i<15)&&(j>3))&&(board[i+1][j-1] == 1)&&(board[i+2][j-2] == 1)&&(board[i+3][j-3] == 1)&&((board[i+4][j-4] == 0)||(board[i-1][j+1] == 0))))){
                    printf("1:%d,%d\n",i+1,j+1);
                    cnt = 1;
                    return 0;
            }
            else if((board[i][j] == 2)&&(((board[i][j+1] == 2)&&(board[i][j+2] == 2)&&(board[i][j+3] == 2)&&(j<15)&&((board[i][j+4] == 0)||(board[i][j-1] == 0)))||((i<15)&&(board[i+1][j] == 2)&&(board[i+2][j] == 2)&&(board[i+3][j] == 2)&&((board[i+4][j] == 0)||(board[i-1][j] == 0)))||(((i<15)&&(j<15))&&(board[i+1][j+1] == 2)&&(board[i+2][j+2] == 2)&&(board[i+3][j+3] == 2)&&((board[i+4][j+4] == 0)||(board[i-1][j-1] == 0)))||(((i<15)&&(j>3))&&(board[i+1][j-1] == 2)&&(board[i+2][j-2] == 2)&&(board[i+3][j-3] == 2)&&((board[i+4][j-4] == 0)||(board[i-1][j+1] == 0))))){
                    printf("2:%d,%d\n",i+1,j+1);
                    cnt = 2;
                    return 0;
            }
        }
    }
    if(cnt == 0){printf("No\n");}
    return 0;
}

