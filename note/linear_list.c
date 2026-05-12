#include <stdio.h>
int N;
typedef int ElemType;  // 可根据需求替换为其他数据类型
typedef struct Node {
    ElemType data;          // 数据域，存储元素值
    struct Node *link;      // 指针域，指向后继结点
} Node, *Nodeptr;

int insertElem(ElemType list[], int i, ElemType item )//顺序表的插入操作
{
    int k;

    /* 测试空间满否、测试插入位置合适否 */
    if (N==MaxSize || i<0 || i>N)
        return -1;                 /* 插入失败 */

    for( k=N-1; k>=i; k-- )
        list[k+1]=list[k];         /* 元素依次后移一个位置 */

    list[i]=item;                   /* 将item插入表的第i个位置 */
    N++;                            /* 线性表的长度加1 */
    return 1;                       /* 插入成功 */
}

int deleteElem(ElemType list[], int i)   //顺序表的删除操作
{
    int k;

    /* 测试表空和位置合适与否 */
    if(N==0 || i<0 || i>N-1)
        return -1;                     /* 3）异常情况：删除失败 */

    for( k=i+1; k<N; k++ )
        list[k-1]=list[k];            /* 1）元素依次前移一个位置 */

    N--;                               /* 2）线性表的长度减1 */
    return 1;                         /* 删除成功 */
}

Nodeptr createList( int n ) /*创建一个具有n个结点的链表 */
{
    /* list是链表首指针也叫头指针，q指向新申请的结点，p指向尾结点 */
    Nodeptr p, q, list=NULL;
    int i;
    for(i=0;i<n;i++){
        q=(Nodeptr)malloc(sizeof(Node));  /* 申请一个新的链结点 */
        q->data=read();       /* 读取一个数据元素 */
        q->link=NULL;         // 对新结点顺手初始化，是个好习惯
        if (list==NULL)       /*链表为空*/
            list=p=q;
        else
            p->link=q;        /*将新结点q链接在链表尾部 */
        p=q;
    }
    return list;
}

int getLength( Nodeptr list )//获得线性链表的长度
{
    Nodeptr p;      /* p为遍历链表结点的指针 */
    int n=0;        /* 链表的长度置初值0 */
    for(p=list; p!=NULL; p=p->link)
                    /* p依次指向链表的下一结点 */
        n++;       /* 对链表结点累计计数 */

    return n;      /* 返回链表的长度n */
}


int main (){
    printf("hello world");
    return 0;
}

