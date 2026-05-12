#include <stdio.h>

int a[19][19];
int dx[4]={0,1,1,1};
int dy[4]={1,0,1,-1};

int in(int x,int y){
    return x>=0 && x<19 && y>=0 && y<19;
}

int main(){
    for(int i=0;i<19;i++)
        for(int j=0;j<19;j++)
            scanf("%d",&a[i][j]);

    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    if(a[i][j]){
        int c=a[i][j];

        for(int d=0;d<4;d++){
            int k;
            for(k=1;k<4;k++){
                int x=i+dx[d]*k,y=j+dy[d]*k;
                if(!in(x,y)||a[x][y]!=c) break;
            }

            if(k==4){
                int px=i-dx[d],py=j-dy[d];
                int nx=i+dx[d]*4,ny=j+dy[d]*4;

                if(in(px,py)&&a[px][py]==c) continue;

                if((in(px,py)&&a[px][py]==0)||(in(nx,ny)&&a[nx][ny]==0)){
                    printf("%d:%d,%d\n",c,i+1,j+1);
                    return 0;
                }
            }
        }
    }

    printf("No\n");
}