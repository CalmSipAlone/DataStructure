# 链表常见操作与考法总结

## 目录

1. [链表基础概念](#一链表基础概念)
2. [单链表](#二单链表)
3. [双链表](#三双链表)
4. [循环链表](#四循环链表)
5. [静态链表](#五静态链表)
6. [链表常考算法](#六链表常考算法)
7. [易错点与面试坑](#七易错点与面试坑)

---

## 一、链表基础概念

### 1.1 什么是链表

链表是一种**线性表**，但不像顺序表（数组）那样连续存储，而是通过**指针**将一个个结点串联起来。

```
数组： [1] -> [2] -> [3] -> [4]  （连续内存）
链表： [1|*] --> [2|*] --> [3|*] --> [4|/] （离散内存，靠指针连接）
```

### 1.2 链表结点结构

每个结点包含两部分：

| 部分 | 作用 |
|------|------|
| **数据域 (data)** | 存储实际数据 |
| **指针域 (next / prior)** | 存放下一个（或上一个）结点的地址 |

```c
// 单链表结点定义
typedef struct LNode {
    int data;           // 数据域
    struct LNode *next; // 指针域，指向下一个结点
} LNode, *LinkList;
```

### 1.3 头指针 vs 头结点

这是**最基础也最容易搞混**的概念：

| 概念 | 说明 |
|------|------|
| **头指针** | 指向链表第一个结点的指针，**必须要有**（链表以头指针命名） |
| **头结点** | 在第一个结点之前附加的一个结点，**可有可无**，数据域一般不存东西 |

```
带头结点： head -> [头结点|*] -> [a1|*] -> [a2|*] -> ... -> [an|/]
不带头结点： head -> [a1|*] -> [a2|*] -> ... -> [an|/]
```

**带头结点的好处：**
- 插入/删除第一个结点时，不用特殊处理头指针
- 空表和非空表的处理统一

```c
// 带头结点时，空表判断：L->next == NULL
// 不带头结点时，空表判断：L == NULL
```

---

## 二、单链表

### 2.1 结点定义

```c
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
```

### 2.2 初始化

**带头结点初始化：**

```c
bool InitList(LinkList &L) {
    L = (LNode *)malloc(sizeof(LNode));  // 分配头结点
    if (L == NULL) return false;          // 内存不足
    L->next = NULL;                       // 头结点之后暂时没有结点
    return true;
}
```

**不带头结点初始化：**

```c
bool InitList(LinkList &L) {
    L = NULL;      // 空表，没有结点
    return true;
}
```

### 2.3 头插法建立单链表

每次把新结点插在头结点后面。常用于**逆置链表**。

```c
LinkList HeadInsert(LinkList &L) {
    LNode *s;
    int x;
    L = (LinkList)malloc(sizeof(LNode));  // 创建头结点
    L->next = NULL;                       // 初始为空链表

    while (scanf("%d", &x) != EOF) {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;   // 新结点指向原来的第一个结点
        L->next = s;         // 头结点指向新结点
    }
    return L;
}
```

**建立过程示意：**
```
初始： head -> NULL
插入1： head -> [1|/]
插入2： head -> [2|*] -> [1|/]
插入3： head -> [3|*] -> [2|*] -> [1|/]
```

> 头插法得到的链表顺序与输入顺序相反！

### 2.4 尾插法建立单链表

每次把新结点插在链表末尾，需要额外一个 `r` 指针始终指向尾结点。

```c
LinkList TailInsert(LinkList &L) {
    int x;
    L = (LinkList)malloc(sizeof(LNode));
    LNode *r = L;   // r 指向尾结点（初始指向头结点）

    while (scanf("%d", &x) != EOF) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;  // 尾结点指向新结点
        r = s;        // r 更新为新结点
    }
    r->next = NULL;   // 尾结点指针置空
    return L;
}
```

### 2.5 按序号查找结点

```c
LNode *GetElem(LinkList L, int i) {
    if (i < 1) return NULL;   // i 不合法
    LNode *p = L->next;       // 第一个结点
    int j = 1;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;   // 找到返回该结点，没找到（i超长）返回NULL
}
```

> 查找的时间复杂度：**O(n)**

### 2.6 按值查找结点

```c
LNode *LocateElem(LinkList L, ElemType e) {
    LNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;   // 找到返回结点，没找到返回NULL
}
```

### 2.7 插入结点

**在第 i 个位置插入：**

```c
bool InsertNode(LinkList &L, int i, ElemType e) {
    if (i < 1) return false;
    LNode *p = GetElem(L, i - 1);  // 找到第 i-1 个结点
    if (p == NULL) return false;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
```

**核心操作（前插）：**
```
s->next = p->next;
p->next = s;
```
**这两句顺序不能换！** 如果先写 `p->next = s`，就找不到原来的 `p->next` 了。

**前插操作的时间复杂度：O(n)**（因为要找到前驱结点）

---

**后插（已知结点 p，在 p 后面插入）：** O(1)

```c
s->next = p->next;
p->next = s;
// 如果想把新数据放在 p 的前面，可以交换数据域
// s->data = p->data; p->data = e;
```

### 2.8 有序插入（保持升序）⭐⭐⭐

**题目：** 已有递增有序的单链表，插入一个新值后仍然保持升序。

**思路：** 从头遍历，找到第一个比新值大的结点，插在它前面。

```c
void OrderedInsert(LinkList &L, ElemType e) {
    // p 从 head 开始（不是第一个结点！），方便插入
    LNode *p = L;
    LNode *s;

    // 找到第一个 >= e 的结点的前驱
    while (p->next != NULL && p->next->data < e) {
        p = p->next;
    }
    // 此时 p->next 是第一个 >= e 的结点（或 NULL）

    s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
}
```

**过程图解：**
```
已有链表： head -> [1] -> [3] -> [5] -> [7] -> NULL，插入 4

第1步：p 从 head 开始，p->next->data=1 < 4 → p 后移
       head -> [1] -> [3] -> [5] -> [7] -> NULL
       ↑p

第2步：p->next->data=3 < 4 → p 后移
       head -> [1] -> [3] -> [5] -> [7] -> NULL
                       ↑p

第3步：p->next->data=5 ≥ 4 → 停！插在 p 后面
       head -> [1] -> [3] -> [5] -> [7] -> NULL
                       ↑p      ↑p->next

第4步：插入 4
       head -> [1] -> [3] -> [4] -> [5] -> [7] -> NULL ✅
```

**边界情况处理：**

| 情况 | p->next | p->next->data < e | 行为 |
|------|---------|-------------------|------|
| 空表 | NULL | — | 直接插在 head 后面 |
| 插在表头（e 比所有值都小） | 第一个结点 | data > e（不进入循环） | 插在 head 后面 |
| 插在表尾（e 比所有值都大） | NULL | 一直循环到 NULL 才停 | 插在尾结点后面 |
| 插入相同值 | 等于 e 的结点 | data = e（不进循环） | 插在等于 e 的结点前面（稳定） |

> **时间复杂度：O(n)**，需要遍历找到插入位置。但相比无序插入后再排序（O(n log n)），还是高效得多。

**变体：** 如果要求降序，只需将 while 条件改为 `p->next->data > e`。

---

### 2.9 删除结点

**删除第 i 个结点：**

```c
bool DeleteNode(LinkList &L, int i, ElemType &e) {
    if (i < 1) return false;
    LNode *p = GetElem(L, i - 1);  // 找前驱
    if (p == NULL || p->next == NULL) return false;

    LNode *q = p->next;   // q 是待删除结点
    e = q->data;
    p->next = q->next;    // 绕过 q
    free(q);              // 释放内存
    return true;
}
```

**核心操作：**
```
p->next = p->next->next;
```

**删除指定结点（已知结点 p 本身）：** O(1)

```c
// 不用找前驱，用"偷天换日"法
bool DeleteNode(LNode *p) {
    if (p == NULL) return false;
    LNode *q = p->next;
    p->data = p->next->data;  // 把后继的数据拿过来
    p->next = q->next;        // 绕过 q
    free(q);
    return true;
}
```

> ⚠️ 如果 p 是最后一个结点，此方法不行！这种情况还是得找前驱。

### 2.10 求表长

```c
int Length(LinkList L) {
    LNode *p = L->next;
    int len = 0;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}
```

---

## 三、双链表

### 3.1 为什么需要双链表

单链表找**前驱**需要 O(n)，双链表每个结点有两个指针：
- `prior`：指向前驱
- `next`：指向后继

```c
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;
```

### 3.2 双链表的插入

**在 p 后面插入 s：**

```c
s->next = p->next;
s->prior = p;
if (p->next != NULL)     // 如果 p 不是最后一个结点
    p->next->prior = s;
p->next = s;
```

```
插入前： ... -> [p] <-> [p->next] -> ...
插入后： ... -> [p] <-> [s] <-> [p->next] -> ...
```

### 3.3 双链表的删除

**删除 p 的后继结点 q：**

```c
p->next = q->next;
if (q->next != NULL)         // 如果 q 不是最后一个结点
    q->next->prior = p;
free(q);
```

### 3.4 双链表的删除自己

```c
p->prior->next = p->next;
p->next->prior = p->prior;
free(p);
```

### 3.5 双链表的有序插入（保持升序）⭐⭐⭐

**题目：** 已有递增有序的双链表，插入一个新值后仍然保持升序。

**思路：** 与单链表类似，遍历找到第一个比新值大的结点，插在它前面。但双链表可以利用 `prior` 指针更方便地处理前驱关系。

```c
void DLinkOrderedInsert(DLinkList &L, ElemType e) {
    DNode *p = L->next;   // p 从第一个结点开始
    DNode *s;

    // 找到第一个 >= e 的结点
    while (p != NULL && p->data < e) {
        p = p->next;
    }
    // 此时 p 是第一个 >= e 的结点（或 NULL）
    // 新结点 s 要插在 p 的前面

    s = (DNode *)malloc(sizeof(DNode));
    s->data = e;

    if (p != NULL) {
        // 情况1：插在 p 的前面（p 不是头结点后的第一个结点时，就是中间/开头）
        s->prior = p->prior;     // s 的前驱指向 p 的前驱
        s->next = p;             // s 的后继指向 p
        p->prior->next = s;      // p 的前驱的后继指向 s
        p->prior = s;            // p 的前驱指向 s
    } else {
        // 情况2：p == NULL，说明 e 最大，插在末尾
        // 需要找到尾结点（或者用 L 的前驱找尾结点，但这里用遍历）
        DNode *tail = L;
        while (tail->next != NULL)
            tail = tail->next;
        // 或者如果 L 是循环双链表：tail = L->prior;

        s->prior = tail;
        s->next = NULL;
        tail->next = s;
    }
}
```

**优化版（带尾指针的循环双链表）：**

如果链表是**循环双链表**，且我们有一个尾指针 `r`，代码会简洁很多：

```c
void DLinkOrderedInsertWithTail(DLinkList &L, DNode *r, ElemType e) {
    // 假设：L 是带头结点的循环双链表，r 指向尾结点（即 L->prior）
    DNode *p = L->next;   // 第一个结点
    DNode *s;

    // 找第一个 >= e 的结点
    while (p != L && p->data < e) {  // 循环链表：p != L 表示没走完一圈
        p = p->next;
    }

    s = (DNode *)malloc(sizeof(DNode));
    s->data = e;

    // 插在 p 前面（p 可能是头结点 L 或某个数据结点）
    s->prior = p->prior;
    s->next = p;
    p->prior->next = s;
    p->prior = s;
}
```

> 循环双链表的好处：**p 遍历到头结点 L 时，说明 e 最大**，直接插在 L 前面（即表尾），不需要单独处理末尾情况。

**过程图解（循环双链表）：**
```
已有链表： L <-> [1] <-> [3] <-> [5] <-> [7] <-> L（循环），插入 4

第1步：p = L->next = [1], p->data=1 < 4 → p = p->next
第2步：p = [3], p->data=3 < 4 → p = p->next
第3步：p = [5], p->data=5 ≥ 4 → 停！插在 [5] 前面

操作：
  s->prior = [5]->prior = [3]
  s->next = [5]
  [3]->next = s
  [5]->prior = s

结果：
  L <-> [1] <-> [3] <-> [4] <-> [5] <-> [7] <-> L ✅
```

**单链表 vs 双链表有序插入对比：**

| 对比项 | 单链表 | 双链表 |
|--------|--------|--------|
| 需要指针 | p 定位到前驱结点 | p 直接定位到目标结点 |
| 插入代码 | 只需改 next | 需改 prior 和 next |
| 末尾处理 | 走完整条链 | 普通链表也需走完；循环链表 O(1) |
| 复杂度 | O(n) | O(n)（循环双链 O(1) 找尾） |

**小技巧：** 单链表找前驱麻烦，所以 p 停在 `第一个 >= e 的结点`的**前驱**；双链表可以直接找 `第一个 >= e 的结点`，因为可以通过 `p->prior` 拿到前驱。

---

## 四、循环链表

### 4.1 循环单链表

最后一个结点的 `next` 不是 NULL，而是指向**头结点**。

```
head -> [a1|*] -> [a2|*] -> ... -> [an|*] --+
          ^                                   |
          +-----------------------------------+ (指向头结点)
```

**判断空表条件：** `L->next == L`

**判断是否为尾结点：** `p->next == L`

**优点：** 从表中任意位置出发，都能遍历整个链表。

### 4.2 循环双链表

头结点的 `prior` 指向尾结点，尾结点的 `next` 指向头结点。

```
head <-> [a1] <-> [a2] <-> ... <-> [an] <-> head
```

**判断空表条件：** `L->next == L && L->prior == L`

### 4.3 常用优化：只设尾指针

对于循环单链表，如果**只设置尾指针 `r`**，那么：
- 第一个结点：`r->next->next`
- 最后一个结点：`r`
- 头结点：`r->next`

这样**在表头和表尾插入都是 O(1)**，非常实用！

```
r -> [an]   (r 指向尾结点)
r->next 就是头结点
```

---

## 五、静态链表

### 5.1 概念

用**数组**实现的链表，每个结点包含数据和**游标（cur）**，游标指向下一个结点的数组下标。

```c
#define MaxSize 100
typedef struct {
    ElemType data;
    int cur;    // 游标，指向下一个元素的数组下标（类似指针）
} SLinkList[MaxSize];
```

```
下标： 0    1    2    3    4    5
     [头|3] [A|2] [B|5] [C|4] [D|-1] [E|0]
     表示链表：头 -> C -> D -> E -> A -> B -> 结束（-1表示NULL）
```

### 5.2 特点

- 插入/删除不需要移动数据，只需要修改游标
- 不适合长度变化大的场景（数组大小固定）
- 需要自己管理空闲结点（malloc/free 得自己实现）

### 5.3 空闲链表管理

通常把空闲结点串成一个链表（空闲链表）：

```
初始化：将数组所有空闲位置用游标串起来
分配：从空闲链表中取一个结点
释放：将删除的结点放回空闲链表
```

---

## 六、链表常考算法

### 考题 1：头插法逆置链表 ⭐⭐⭐

**题目：** 给定一个单链表，将其原地逆置（不允许申请新结点空间）。

**思路：** 将原链表摘下，用头插法重新插入。

```c
void ReverseList(LinkList &L) {
    LNode *p = L->next;   // p 指向第一个结点
    LNode *q;
    L->next = NULL;       // 将头结点摘下

    while (p != NULL) {
        q = p->next;      // 暂存 p 的后继（因为 p 马上要插到头结点后面）
        p->next = L->next; // 头插法核心
        L->next = p;
        p = q;            // 继续处理下一个结点
    }
}
```

**过程图解：**
```
原链表： head -> [1] -> [2] -> [3] -> [4] -> NULL

第1步： head->next = NULL（摘下）
       head -> NULL,  p 指向 [1]

第2步： 头插 [1]
       head -> [1] -> NULL

第3步： 头插 [2]
       head -> [2] -> [1] -> NULL

第4步： 头插 [3]
       head -> [3] -> [2] -> [1] -> NULL

第5步： 头插 [4]
       head -> [4] -> [3] -> [2] -> [1] -> NULL ✅
```

**变体：** 逆序输出链表（不改变链表结构）
- 可以用栈（或递归），利用递归的栈特性，在递归返回时打印

```c
void ReversePrint(LNode *p) {
    if (p != NULL) {
        ReversePrint(p->next);
        printf("%d ", p->data);  // 回溯时打印
    }
}
// 调用：ReversePrint(L->next);
```

---

### 考题 2：链表归并（合并两个有序链表）⭐⭐⭐

**题目：** 将两个递增有序的单链表合并成一个递减有序的单链表。

**思路：** 归并 + 头插法（想要递减，用头插即可）。

```c
void MergeList(LinkList &A, LinkList &B) {
    LNode *pa = A->next, *pb = B->next;
    LNode *r;               // 暂存指针
    A->next = NULL;         // 将 A 头结点摘下，准备头插

    while (pa != NULL && pb != NULL) {
        if (pa->data <= pb->data) {
            r = pa->next;
            pa->next = A->next;  // 头插 pa
            A->next = pa;
            pa = r;
        } else {
            r = pb->next;
            pb->next = A->next;  // 头插 pb
            A->next = pb;
            pb = r;
        }
    }

    // 处理剩余部分
    while (pa != NULL) {
        r = pa->next;
        pa->next = A->next;
        A->next = pa;
        pa = r;
    }
    while (pb != NULL) {
        r = pb->next;
        pb->next = A->next;
        A->next = pb;
        pb = r;
    }

    // 释放 B 的头结点
    free(B);
}
```

---

### 考题 3：寻找中间结点 / 倒数第 k 个结点 ⭐⭐⭐⭐

**题目：** 查找单链表的中间结点（只能遍历一次）。

**解法：快慢指针（双指针）**

```c
LNode *FindMiddle(LinkList L) {
    LNode *slow = L->next;   // 慢指针一次走一步
    LNode *fast = L->next;   // 快指针一次走两步

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 当 fast 走到末尾时，slow 正好在中间
    return slow;
}
```

**查找倒数第 k 个结点：**

```c
LNode *FindLastK(LinkList L, int k) {
    LNode *fast = L->next;
    LNode *slow = L->next;

    // fast 先走 k 步
    for (int i = 0; i < k; i++) {
        if (fast == NULL) return NULL;  // k 太大
        fast = fast->next;
    }

    // 然后 slow 和 fast 一起走
    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```

> **原理：** fast 和 slow 始终保持 k 的距离，fast 到末尾时，slow 就是倒数第 k 个。

---

### 考题 4：判断链表是否有环 ⭐⭐⭐⭐

**题目：** 判断单链表是否有环，并找出环的入口。

**解法：快慢指针**

```c
LNode *FindCycle(LinkList L) {
    LNode *slow = L->next;
    LNode *fast = L->next;

    // 第一步：判断是否有环
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;      // 相遇，说明有环
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;                  // 无环

    // 第二步：找环的入口
    // 原理：从相遇点和头结点同时出发，再次相遇就是环入口
    slow = L->next;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;  // 环的入口结点
}
```

**数学原理：**

```
从头结点到环入口的距离：a
从环入口到相遇点的距离：b
从相遇点回到环入口的距离：c

slow 走过的距离：a + b
fast 走过的距离：a + b + (b + c)  // fast 比 slow 多走了一圈
因为 fast = 2 * slow
所以：a + b + b + c = 2(a + b)
            a = c  ✅
```
所以从头和相遇点同时出发，每次走一步，相遇点就是环入口。

---

### 考题 5：删除链表中的重复元素 ⭐⭐⭐

**有序链表去重：**

```c
void DeleteDuplicate(LinkList L) {
    LNode *p = L->next;
    LNode *q;

    while (p != NULL && p->next != NULL) {
        if (p->data == p->next->data) {
            q = p->next;
            p->next = q->next;
            free(q);
        } else {
            p = p->next;
        }
    }
}
```

**无序链表去重：** 用哈希表记录已经出现过的值（时间换空间：O(n^2) 或 用辅助数组）。

---

### 考题 6：两个链表的公共结点 ⭐⭐⭐

**题目：** 找出两个单链表的第一个公共结点（Y 型链表）。

```
链表A： a1 -> a2 -> a3 -> c1 -> c2 -> c3
                            /
链表B： b1 -> b2 -> b3 -> c1
```

**思路：** 长的链表先走 `|lenA - lenB|` 步，然后一起走。

```c
LNode *FindCommon(LinkList A, LinkList B) {
    int lenA = Length(A), lenB = Length(B);
    LNode *p = A->next, *q = B->next;
    int diff = abs(lenA - lenB);

    // 长的先走
    if (lenA > lenB) {
        while (diff--) p = p->next;
    } else {
        while (diff--) q = q->next;
    }

    // 一起走，相遇处就是第一个公共结点
    while (p != NULL && q != NULL) {
        if (p == q) return p;   // 注意：是比较地址（结点本身），不是数据
        p = p->next;
        q = q->next;
    }
    return NULL;  // 没有公共结点
}
```

---

### 考题 7：分割链表 ⭐⭐⭐

**题目：** 将链表中小于 x 的结点移到大于等于 x 的结点之前（类似快排的 partition）。

**思路：** 拆成两个链表，再拼起来。

```c
void PartitionList(LinkList L, int x) {
    LNode *smallHead = (LNode *)malloc(sizeof(LNode));  // < x 的链表
    LNode *bigHead = (LNode *)malloc(sizeof(LNode));    // >= x 的链表
    LNode *s = smallHead, *b = bigHead;
    LNode *p = L->next;

    while (p != NULL) {
        if (p->data < x) {
            s->next = p;
            s = p;
        } else {
            b->next = p;
            b = p;
        }
        p = p->next;
    }

    b->next = NULL;          // 大链表的尾巴置空
    s->next = bigHead->next;  // 小链表接上大链表
    L->next = smallHead->next; // 头指针指向合并后的链表

    free(smallHead);
    free(bigHead);
}
```

---

### 考题 8：单链表排序 ⭐⭐⭐

**题目：** 对单链表进行排序（不能用数组辅助）。

**解法：归并排序（适合链表）**

```c
// 找中间结点（快慢指针）
LNode *FindMid(LNode *head) {
    LNode *slow = head, *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 合并两个有序链表
LNode *Merge(LNode *left, LNode *right) {
    LNode dummy, *cur = &dummy;
    while (left != NULL && right != NULL) {
        if (left->data < right->data) {
            cur->next = left;
            left = left->next;
        } else {
            cur->next = right;
            right = right->next;
        }
        cur = cur->next;
    }
    cur->next = (left != NULL) ? left : right;
    return dummy.next;
}

// 归并排序主函数
LNode *MergeSort(LNode *head) {
    if (head == NULL || head->next == NULL) return head;

    LNode *mid = FindMid(head);
    LNode *rightHead = mid->next;
    mid->next = NULL;  // 断开链表

    LNode *left = MergeSort(head);
    LNode *right = MergeSort(rightHead);
    return Merge(left, right);
}

// 调用：L->next = MergeSort(L->next);
```

---

### 考题 9：判断链表是否回文 ⭐⭐⭐

**题目：** 判断单链表是否为回文（如 1->2->3->2->1）。

**思路：** 快慢指针找中点 → 反转后半段 → 比较 → 恢复原链表

```c
bool IsPalindrome(LinkList L) {
    if (L->next == NULL || L->next->next == NULL) return true;

    // 1. 找中间结点
    LNode *slow = L->next, *fast = L->next;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2. 反转后半部分
    LNode *head2 = slow->next;
    slow->next = NULL;  // 断开

    LNode *p = head2, *q;
    head2 = NULL;
    while (p != NULL) {
        q = p->next;
        p->next = head2;
        head2 = p;
        p = q;
    }

    // 3. 比较
    LNode *left = L->next, *right = head2;
    bool flag = true;
    while (right != NULL) {
        if (left->data != right->data) {
            flag = false;
            break;
        }
        left = left->next;
        right = right->next;
    }

    // 4. 恢复后半部分（再反转回来）
    p = head2;
    head2 = NULL;
    while (p != NULL) {
        q = p->next;
        p->next = head2;
        head2 = p;
        p = q;
    }
    slow->next = head2;

    return flag;
}
```

---

### 考题 10：循环链表的约瑟夫问题 ⭐⭐

**题目：** n 个人围成一圈，从第一个人开始报数，报到 m 的人出列，求最后剩下的人。

```c
int Josephus(int n, int m) {
    // 建立循环单链表
    LNode *head = (LNode *)malloc(sizeof(LNode));
    LNode *r = head;  // 尾指针
    for (int i = 1; i <= n; i++) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = i;
        r->next = s;
        r = s;
    }
    r->next = head->next;  // 首尾相连（跳过头结点）
    free(head);

    // 开始模拟
    LNode *p = r;      // p 指向最后一个结点（在第一个结点之前）
    while (p->next != p) {  // 只剩一个结点时结束
        for (int i = 1; i < m; i++)
            p = p->next;    // 走 m-1 步，到达要删除结点的前驱
        LNode *q = p->next; // 要删除的结点
        p->next = q->next;
        printf("%d ", q->data);
        free(q);
    }
    return p->data;  // 最后剩下的人
}
```

**数学解法（不用链表）：** 递推公式 `f(1) = 0; f(n) = (f(n-1) + m) % n`（这里编号从 0 开始）。

---

## 七、易错点与面试坑

### 7.1 常见错误

| 错误 | 后果 | 正确做法 |
|------|------|----------|
| 插入/删除顺序反了 | 丢失后继结点 | 先连后断：先接新结点再断旧链 |
| 忘记检查 `p == NULL` | 空指针异常 | 访问 `p->next` 前先检查 p |
| 忘记置尾结点 `next = NULL` | 遍历越界 | 尾插后一定要 `r->next = NULL` |
| 释放 `free(p)` 后还访问 | 悬垂指针 | 释放后不再使用，或置 NULL |
| 在双链表删除时忘记处理 `prior` | 前驱链断裂 | 双向都要更新 |

### 7.2 核心口诀

```
链表操作要小心，先连后断记在心。
头插尾插要分清，逆置就用头插法。
快慢指针用处多，中点环口都能做。
归并排序用递归，两个有序来合并。
插入删除找前驱，双链就省这一步。
```

### 7.3 复杂度总结

| 操作 | 单链表（不带头结点） | 单链表（带头结点） | 双链表 |
|------|---------------------|-------------------|--------|
| 头插 | O(1) | O(1) | O(1) |
| 尾插 | O(n) | O(n) | O(1)（有尾指针） |
| 中间插 | O(n) | O(n) | O(n)（找位置） |
| 按值查找 | O(n) | O(n) | O(n) |
| 按序查找 | O(n) | O(n) | O(n) |
| 删除已知结点 | O(n)（需找前驱） | O(n) | O(1) |

### 7.4 做题三步走

1. **画图！画图！画图！** 链表题目只要画出示意图，思路就清晰了
2. **想好边界条件：** 空链表、只有一个结点、首尾操作
3. **验证：** 用简单例子在纸上跑一遍代码
