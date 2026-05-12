# C 语言 `<ctype.h>` 全套函数详解
`<ctype.h>` 专门用来**判断字符类型、大小写转换**，所有函数参数都是 `int` 类型（建议传 `unsigned char` 避免乱码报错），**判断类函数：返回非0=真，返回0=假**。

## 一、字符判断类函数
### 1. `isalpha(int c)`
**作用**：判断是不是**英文字母**（大写 A-Z / 小写 a-z）
```c
#include <stdio.h>
#include <ctype.h>
int main() {
    char c = 'a';
    if (isalpha(c)) {
        printf("是字母\n");
    }
    return 0;
}
```

### 2. `isdigit(int c)`
**作用**：判断是不是**数字 0~9**

### 3. `isalnum(int c)`
**作用**：判断是不是**字母 或 数字**（alphanumeric）

### 4. `islower(int c)`
**作用**：判断是不是**小写字母 a~z**

### 5. `isupper(int c)`
**作用**：判断是不是**大写字母 A~Z**

### 6. `isspace(int c)`
**作用**：判断是不是**空白字符**
包含：空格 ` `、制表符 `\t`、换行 `\n`、回车 `\r`、`\v`、`\f`

### 7. `isblank(int c)`
**作用**：只判断**空格 或 制表符 \t**（比 isspace 范围小）

### 8. `ispunct(int c)`
**作用**：判断是不是**标点符号**（! @ # $ , . ; 等）

### 9. `isxdigit(int c)`
**作用**：判断是不是**十六进制字符**
0-9、a-f、A-F

### 10. `isprint(int c)`
**作用**：是不是**可打印字符**（包含空格、字母、数字、标点）

### 11. `isgraph(int c)`
**作用**：可打印**非空白**字符（不含空格）

### 12. `iscntrl(int c)`
**作用**：是不是**控制字符**（不可打印：ASCII 0~31、127）

---

## 二、大小写转换函数
### 1. `tolower(int c)`
**作用**：大写字母转**小写**，不是字母则原样返回
```c
char ch = 'A';
ch = tolower(ch);  // 变成 'a'
```

### 2. `toupper(int c)`
**作用**：小写字母转**大写**，不是字母则原样返回
```c
char ch = 'b';
ch = toupper(ch);  // 变成 'B'
```

---

## 三、通用使用注意事项（必看）
1. 不要直接传普通 `char` 给带中文/扩展ASCII的字符，建议强转：
   ```c
   isalpha( (unsigned char)c );
   ```
2. 这些函数**只能处理单个字符**，处理字符串要循环遍历每一位；
3. 判断函数返回值**不要直接和 1 比较**，只要判断 `if(isdigit(c))` 就行。

---

## 四、常用一句话速记
- 字母：`isalpha`
- 数字：`isdigit`
- 字母+数字：`isalnum`
- 大小写判断：`islower` / `isupper`
- 大小写转换：`tolower` / `toupper`
- 空白：`isspace` / `isblank`

# C语言 `<string.h>` 常用函数大全
全部是**字符串、内存操作**函数，必须头文件：
```c
#include <string.h>
```

## 一、求字符串长度
### 1. `strlen(str)`
**功能**：返回字符串**实际长度**（**不包含 `\0`**）
```c
char s[] = "hello";
int len = strlen(s);  
// len = 5
```

---

## 二、字符串复制
### 2. `strcpy(目标, 源)`
**功能**：把源字符串**完整复制**到目标，自带补 `\0`
⚠️ 不安全：容易数组越界
```c
char a[20];
char b[] = "hello";
strcpy(a, b);  // a = "hello"
```

### 3. `strncpy(目标, 源, n)`
**功能**：最多复制 **n 个字符**，安全版
```c
strncpy(a, b, 3); // 只复制前3个
```

---

## 三、字符串拼接
### 4. `strcat(目标, 源)`
**功能**：把源字符串**拼接到目标末尾**
```c
char a[20] = "hi ";
char b[] = "tom";
strcat(a, b);  
// a = "hi tom"
```

### 5. `strncat(目标, 源, n)`
**功能**：最多拼接 **n 个字符**，安全版

---

## 四、字符串比较
### 6. `strcmp(s1, s2)`
**功能**：按ASCII比较两个字符串
- 返回 **0** → 两个字符串相等
- 返回 >0 → s1 更大
- 返回 <0 → s1 更小
```c
if(strcmp("abc", "abc") == 0){
    printf("相等");
}
```

### 7. `strncmp(s1, s2, n)`
**功能**：只比较前 **n 个字符**

---

## 五、字符查找
### 8. `strchr(str, ch)`
**功能**：从左往右找**第一个**出现的字符 ch
找到返回地址，没找到返回 `NULL`

### 9. `strrchr(str, ch)`
**功能**：从右往左找**最后一个**出现的字符 ch

---

## 六、字符串匹配
### 10. `strstr(母串, 子串)`
**功能**：在母串中查找**子串第一次出现的位置**
找不到返回 `NULL`
```c
char s[] = "hello world";
char *p = strstr(s, "world"); 
// 指向 world 开头
```

---

## 七、字符串分割
### 11. `strtok(字符串, 分隔符)`
**功能**：按指定符号**切割字符串**
例：按空格、逗号分割句子

---

## 八、内存操作（非常常用）
### 12. `memset(地址, 填充值, 字节数)`
**功能**：批量初始化内存，**清零数组神器**
```c
int arr[10];
memset(arr, 0, sizeof(arr)); // 全部置0
```

### 13. `memcpy(目标, 源, 字节数)`
**功能**：内存拷贝，不管有没有字符串结束符

### 14. `memmove(目标, 源, 字节数)`
**功能**：安全内存拷贝，**允许地址重叠**

### 15. `memcmp(p1, p2, 字节数)`
**功能**：按内存字节逐一比较

---

# 超常用速记口诀
1. `strlen` 求长度
2. `strcpy` 复制、`strcat` 拼接
3. `strcmp` 比大小
4. `strchr` 找字符、`strstr` 找子串
5. `memset` 清空数组必用


# C语言 单链表**全部常用操作** 手把手演示
我给你写**完整可直接运行代码**，包含所有必考常用操作，每一步都有注释、逐个演示。

## 一、链表常用操作列表
1. 定义链表节点
2. 头插法建链表
3. 尾插法建链表
4. 遍历打印链表
5. 获取链表长度
6. 按**位置**插入节点
7. 按**值**查找节点
8. 按**位置**删除节点
9. 按**值**删除节点
10. 链表反转
11. 清空/销毁整个链表

---

## 二、完整代码（所有操作一次性演示）
```c
#include <stdio.h>
#include <stdlib.h>

// 1. 定义单链表节点结构
typedef struct LNode {
    int data;               // 数据域
    struct LNode *next;     // 指针域，指向下一个节点
} LNode, *LinkList;

// 遍历打印链表
void printList(LinkList head) {
    LNode *p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 2. 尾插法 创建链表
void createTail(LinkList head, int arr[], int n) {
    LNode *tail = head;
    for (int i = 0; i < n; i++) {
        // 新建节点
        LNode *newNode = (LNode *)malloc(sizeof(LNode));
        newNode->data = arr[i];
        newNode->next = NULL;

        tail->next = newNode;
        tail = newNode;
    }
}

// 3. 头插法 插入一个节点
void insertHead(LinkList head, int val) {
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = val;
    newNode->next = head->next;
    head->next = newNode;
}

// 4. 获取链表长度
int getLength(LinkList head) {
    int len = 0;
    LNode *p = head->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 5. 按位置插入：在第 pos 个位置插入 val
int insertByPos(LinkList head, int pos, int val) {
    if (pos < 1) return 0;
    LNode *p = head;
    // 找到第 pos-1 个节点
    for (int i = 1; i < pos && p; i++) {
        p = p->next;
    }
    if (!p) return 0;

    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = val;
    newNode->next = p->next;
    p->next = newNode;
    return 1;
}

// 6. 按值查找，返回所在位置，没找到返回 -1
int findByVal(LinkList head, int val) {
    int pos = 1;
    LNode *p = head->next;
    while (p) {
        if (p->data == val) return pos;
        p = p->next;
        pos++;
    }
    return -1;
}

// 7. 按位置删除
int deleteByPos(LinkList head, int pos) {
    if (pos < 1) return 0;
    LNode *p = head;
    for (int i = 1; i < pos && p->next; i++) {
        p = p->next;
    }
    if (!p->next) return 0;

    LNode *del = p->next;
    p->next = del->next;
    free(del);
    return 1;
}

// 8. 按值删除第一个匹配的节点
void deleteByVal(LinkList head, int val) {
    LNode *p = head;
    while (p->next && p->next->data != val) {
        p = p->next;
    }
    if (p->next) {
        LNode *del = p->next;
        p->next = del->next;
        free(del);
    }
}

// 9. 链表反转
void reverseList(LinkList head) {
    LNode *pre = NULL;
    LNode *cur = head->next;
    LNode *next;

    while (cur) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = pre;
}

// 10. 销毁链表
void destroyList(LinkList head) {
    LNode *p, *q;
    p = head;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
}

// 主函数：逐个演示所有操作
int main() {
    // 创建头结点
    LinkList head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;

    int arr[] = {10, 20, 30, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("==== 1. 尾插法建链表 ====\n");
    createTail(head, arr, n);
    printList(head);

    printf("==== 2. 头插法插入 5 ====\n");
    insertHead(head, 5);
    printList(head);

    printf("==== 3. 链表长度 ====\n");
    printf("len = %d\n", getLength(head));

    printf("==== 4. 在第3个位置插入 99 ====\n");
    insertByPos(head, 3, 99);
    printList(head);

    printf("==== 5. 查找值为30的位置 ====\n");
    int pos = findByVal(head, 30);
    printf("30 在第 %d 位\n", pos);

    printf("==== 6. 删除第2个位置节点 ====\n");
    deleteByPos(head, 2);
    printList(head);

    printf("==== 7. 删除值为99的节点 ====\n");
    deleteByVal(head, 99);
    printList(head);

    printf("==== 8. 链表反转 ====\n");
    reverseList(head);
    printList(head);

    // 销毁链表，释放内存
    destroyList(head);
    return 0;
}
```

---

## 三、运行效果预览
```
==== 1. 尾插法建链表 ====
10 20 30 40
==== 2. 头插法插入 5 ====
5 10 20 30 40
==== 3. 链表长度 ====
len = 5
==== 4. 在第3个位置插入 99 ====
5 10 99 20 30 40
==== 5. 查找值为30的位置 ====
30 在第 5 位
==== 6. 删除第2个位置节点 ====
5 99 20 30 40
==== 7. 删除值为99的节点 ====
5 20 30 40
==== 8. 链表反转 ====
40 30 20 5
```

---
# C 语言 **双向链表** 全套常用操作（带头结点、可直接运行）
包含：定义节点、头插、尾插、正序遍历、逆序遍历、按位置插/删、按值查/删、求长度、销毁链表。

## 完整代码
```c
#include <stdio.h>
#include <stdlib.h>

// 1. 定义双向链表节点
typedef struct DNode
{
    int data;
    struct DNode *prev;   // 前驱指针
    struct DNode *next;   // 后继指针
} DNode, *DLinkList;

// 2. 正序遍历打印
void printForward(DLinkList head)
{
    DNode *p = head->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 3. 逆序遍历打印（双向链表独有）
void printBackward(DLinkList head)
{
    // 先走到最后一个节点
    DNode *p = head->next;
    if (p == NULL) return;

    while (p->next != NULL)
        p = p->next;

    // 往前倒着遍历
    while (p != head)
    {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
}

// 4. 尾插法 创建双向链表
void createByTail(DLinkList head, int arr[], int n)
{
    DNode *tail = head;
    for (int i = 0; i < n; i++)
    {
        // 新建节点
        DNode *newNode = (DNode *)malloc(sizeof(DNode));
        newNode->data = arr[i];
        newNode->prev = tail;
        newNode->next = NULL;

        tail->next = newNode;
        tail = newNode;
    }
}

// 5. 头插法 插入一个元素
void insertByHead(DLinkList head, int val)
{
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = val;

    newNode->next = head->next;
    if (head->next != NULL)
        head->next->prev = newNode;

    newNode->prev = head;
    head->next = newNode;
}

// 6. 获取链表长度
int getLength(DLinkList head)
{
    int len = 0;
    DNode *p = head->next;
    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}

// 7. 按位置插入：第 pos 个位置插入 val
int insertByPos(DLinkList head, int pos, int val)
{
    if (pos < 1) return 0;
    DNode *p = head;
    // 找到第 pos-1 个节点
    for (int i = 1; i < pos && p; i++)
        p = p->next;

    if (!p) return 0;

    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = val;

    // 双向指针重连
    newNode->prev = p;
    newNode->next = p->next;
    if (p->next != NULL)
        p->next->prev = newNode;
    p->next = newNode;

    return 1;
}

// 8. 按值查找，返回位置，没找到返回 -1
int findByVal(DLinkList head, int val)
{
    int pos = 1;
    DNode *p = head->next;
    while (p)
    {
        if (p->data == val)
            return pos;
        p = p->next;
        pos++;
    }
    return -1;
}

// 9. 按位置删除
int deleteByPos(DLinkList head, int pos)
{
    if (pos < 1) return 0;
    DNode *p = head->next;
    for (int i = 1; i < pos && p; i++)
        p = p->next;

    if (!p) return 0;

    // 跳过被删节点
    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;

    free(p);
    return 1;
}

// 10. 按值删除第一个匹配节点
void deleteByVal(DLinkList head, int val)
{
    DNode *p = head->next;
    while (p && p->data != val)
        p = p->next;

    if (!p) return;

    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;

    free(p);
}

// 11. 销毁整个双向链表
void destroyList(DLinkList head)
{
    DNode *p, *q;
    p = head;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

// 主函数：演示所有操作
int main()
{
    // 创建头结点
    DLinkList head = (DNode *)malloc(sizeof(DNode));
    head->prev = NULL;
    head->next = NULL;

    int arr[] = {10, 20, 30, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("==== 1. 尾插法建表 正序 ====\n");
    createByTail(head, arr, n);
    printForward(head);

    printf("==== 2. 逆序遍历 ====\n");
    printBackward(head);

    printf("==== 3. 头插 5 ====\n");
    insertByHead(head, 5);
    printForward(head);

    printf("==== 4. 链表长度 ====\n");
    printf("len = %d\n", getLength(head));

    printf("==== 5. 第3位插入 99 ====\n");
    insertByPos(head, 3, 99);
    printForward(head);

    printf("==== 6. 查找30的位置 ====\n");
    printf("30 在第 %d 位\n", findByVal(head, 30));

    printf("==== 7. 删除第2个节点 ====\n");
    deleteByPos(head, 2);
    printForward(head);

    printf("==== 8. 删除值为99 ====\n");
    deleteByVal(head, 99);
    printForward(head);

    // 释放内存
    destroyList(head);
    return 0;
}
```

## 运行输出
```
==== 1. 尾插法建表 正序 ====
10 20 30 40
==== 2. 逆序遍历 ====
40 30 20 10
==== 3. 头插 5 ====
5 10 20 30 40
==== 4. 链表长度 ====
len = 5
==== 5. 第3位插入 99 ====
5 10 99 20 30 40
==== 6. 查找30的位置 ====
30 在第 5 位
==== 7. 删除第2个节点 ====
5 99 20 30 40
==== 8. 删除值为99 ====
5 20 30 40
```