# qsort 函数与各种 cmp 写法完全指南

## 目录

1. [qsort 函数原型](#一qsort-函数原型)
2. [cmp 函数的核心规则](#二cmp-函数的核心规则)
3. [基本类型排序](#三基本类型排序)
4. [一维数组排序](#四一维数组排序)
5. [二维数组排序](#五二维数组排序)
6. [结构体排序](#六结构体排序)
7. [字符串排序](#七字符串排序)
8. [指针数组排序](#八指针数组排序)
9. [降序与复杂规则](#九降序与复杂规则)
10. [bsearch 二分查找](#十bsearch-二分查找)
11. [常考题型](#十一常考题型)
12. [速查表](#十二速查表)

---

## 一、qsort 函数原型

### 1.1 头文件

```c
#include <stdlib.h>
```

### 1.2 函数声明

```c
void qsort(void *base,            // 待排序数组的首地址
           size_t nmemb,          // 数组中元素的个数
           size_t size,           // 每个元素的大小（字节）
           int (*cmp)(const void *, const void *)  // 比较函数
           );
```

### 1.3 参数说明

| 参数 | 含义 | 示例 |
|------|------|------|
| `base` | 数组起始地址 | `a` 或 `&a[0]` |
| `nmemb` | 元素个数 | `n` 或 `sizeof(a)/sizeof(a[0])` |
| `size` | 每个元素字节数 | `sizeof(int)`、`sizeof(struct Student)` |
| `cmp` | 比较函数指针 | 自己写的比较函数名 |

### 1.4 最简单的完整示例

```c
#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = sizeof(a) / sizeof(a[0]);

    qsort(a, n, sizeof(int), cmp_int);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);   // 输出：1 2 3 5 8 9
    return 0;
}
```

---

## 二、cmp 函数的核心规则

### 2.1 函数签名

```c
int cmp(const void *a, const void *b);
```

### 2.2 返回值含义

| 返回值 | 含义 |
|--------|------|
| **负数**（< 0） | a 排在 b **前面**（a < b） |
| **零**（== 0） | a 和 b 相等，顺序无所谓 |
| **正数**（> 0） | a 排在 b **后面**（a > b） |

### 2.3 记忆口诀

```
负前正后，零不动。
（返回负数则 a 在前，正数则 a 在后）
```

### 2.4 通用写法模板

```c
int cmp(const void *a, const void *b) {
    // 1. 先将 void * 强制转换成实际类型的指针
    // 2. 用 * 解引用拿到值
    // 3. 返回差值
}
```

> **关键理解：** `qsort` 内部在比较两个元素时，会调用 `cmp(a, b)`。如果 cmp 返回负数，qsort 就认为 a 应该排在 b 前面。**你只需要告诉 qsort 两个元素谁大谁小，具体怎么排是 qsort 的事。**

---

## 三、基本类型排序

### 3.1 int 类型

```c
int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;  // 升序
}

int cmp_int_desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;  // 降序
}

// 升序调用
qsort(arr, n, sizeof(int), cmp_int);
```

> ⚠️ 注意：`*(int *)a - *(int *)b` 在 int 差值可能溢出时会有问题（比如 a = 2147483647, b = -2147483648），安全写法：

```c
int cmp_int_safe(const void *a, const void *b) {
    int va = *(int *)a;
    int vb = *(int *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}
```

### 3.2 float / double 类型

浮点数**不能用减法**（会有精度问题和截断问题），必须用比较：

```c
// float 升序
int cmp_float(const void *a, const void *b) {
    float va = *(float *)a;
    float vb = *(float *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

// double 升序
int cmp_double(const void *a, const void *b) {
    double va = *(double *)a;
    double vb = *(double *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

// double 降序
int cmp_double_desc(const void *a, const void *b) {
    double va = *(double *)a;
    double vb = *(double *)b;
    if (va > vb) return -1;   // 反向比较
    if (va < vb) return 1;
    return 0;
}
```

> ⚠️ `return *(double *)a - *(double *)b;` 是**错误的**！减法结果会被截断成 int，浮点数差值的小数部分会丢失。

**一个取巧的写法（能用但不太直观）：**
```c
int cmp_double(const void *a, const void *b) {
    return *(double *)a > *(double *)b ? 1 : -1;
}
// 注意：这个写法省略了相等的情况，但因为 qsort 不要求 0 必须严格返回 0，
// 大多数情况下没问题。不过严格来说应该处理相等。
```

### 3.3 char 类型

```c
// char 就是 1 字节的整数，可以当 int 处理
int cmp_char(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

// 大写字母在前，小写字母在后（ASCII 序就是 'A' < 'Z' < 'a' < 'z'）
// 不区分大小写的字母序：
int cmp_char_insensitive(const void *a, const void *b) {
    char va = tolower(*(char *)a);
    char vb = tolower(*(char *)b);
    return va - vb;
}
```

### 3.4 long long 类型

```c
int cmp_ll(const void *a, const void *b) {
    long long va = *(long long *)a;
    long long vb = *(long long *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}
```

---

## 四、一维数组排序

### 4.1 普通一维数组

```c
int a[100];
qsort(a, n, sizeof(int), cmp_int);
```

### 4.2 按绝对值排序

```c
int cmp_abs(const void *a, const void *b) {
    int va = abs(*(int *)a);
    int vb = abs(*(int *)b);
    return va - vb;   // 按绝对值升序
}

// 调用：
int a[] = {-5, 3, -8, 2, -1};
qsort(a, 5, sizeof(int), cmp_abs);
// 结果：-1, 2, 3, -5, -8   （绝对值：1, 2, 3, 5, 8）
```

### 4.3 按奇偶排序（奇数在前，偶数在后）

```c
int cmp_odd_even(const void *a, const void *b) {
    int va = *(int *)a;
    int vb = *(int *)b;
    int odd_a = va % 2;   // 奇数=1，偶数=0
    int odd_b = vb % 2;

    if (odd_a != odd_b)
        return odd_b - odd_a;  // 奇数（1）排在偶数（0）前面
    else
        return va - vb;        // 同为奇数或偶数，按大小排
}

// 调用：
int a[] = {1, 2, 3, 4, 5, 6};
qsort(a, 6, sizeof(int), cmp_odd_even);
// 结果：1, 3, 5, 2, 4, 6
```

> **这段代码的优先级逻辑：** 先按奇偶分（奇数排在偶数前），再按大小排（奇数中小的在前，偶数中小的在前）。

### 4.4 按数字的各位和排序

```c
int digit_sum(int x) {
    int sum = 0;
    x = abs(x);
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int cmp_digit_sum(const void *a, const void *b) {
    return digit_sum(*(int *)a) - digit_sum(*(int *)b);
}
```

---

## 五、二维数组排序

### 5.1 二维数组按行排序

比如按每行的第一个元素排序：

```c
// 二维数组 a[][2] 按第一列升序
int cmp_2d_first(const void *a, const void *b) {
    // a, b 指向的是"一维数组"（每行）
    // (int *)a 是这一行的首地址
    // *(int *)a 是这一行的第一个元素
    int va = *(int *)a;   // 等价于 ((int *)a)[0]
    int vb = *(int *)b;   // 等价于 ((int *)b)[0]
    return va - vb;
}

int a[][2] = {{3, 5}, {1, 8}, {2, 4}, {5, 1}};
int rows = sizeof(a) / sizeof(a[0]);
qsort(a, rows, sizeof(a[0]), cmp_2d_first);
// 结果：{1,8}, {2,4}, {3,5}, {5,1}
```

**按第一列升序，相同则按第二列升序：**

```c
int cmp_2d_both(const void *a, const void *b) {
    int *row_a = (int *)a;
    int *row_b = (int *)b;
    if (row_a[0] != row_b[0])
        return row_a[0] - row_b[0];  // 先按第一列
    return row_a[1] - row_b[1];      // 再按第二列
}
```

### 5.2 区间问题常用：按右端点或左端点排序

```c
// 按右端点升序（贪心算法常用）
int cmp_interval_right(const void *a, const void *b) {
    int *ia = (int *)a;
    int *ib = (int *)b;
    return ia[1] - ib[1];  // 按第二列（右端点）排序
}

// 按左端点升序（合并区间常用）
int cmp_interval_left(const void *a, const void *b) {
    int *ia = (int *)a;
    int *ib = (int *)b;
    return ia[0] - ib[0];  // 按第一列（左端点）排序
}
```

### 5.3 指针数组（数组中的每个元素是指针）

```c
// 对指针数组中的指针指向的 int 值排序
int *arr[100];  // 每个元素是 int *

int cmp_ptr_int(const void *a, const void *b) {
    // a 是 "指针的指针" 的地址
    // *(int **)a 拿到指针，**(int **)a 拿到值
    int va = **(int **)a;
    int vb = **(int **)b;
    return va - vb;
}
```

> 这种情况比较少见，一般用结构体代替。

---

## 六、结构体排序

### 6.1 单关键字排序

```c
typedef struct {
    int id;
    char name[50];
    int score;
} Student;

// 按学号升序
int cmp_by_id(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return sa->id - sb->id;
}

// 按成绩降序
int cmp_by_score_desc(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return sb->score - sa->score;  // 降序：b - a
}

// 按姓名（字典序）
int cmp_by_name(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return strcmp(sa->name, sb->name);  // strcmp 返回值正好符合要求！
}

qsort(stu, n, sizeof(Student), cmp_by_score_desc);
```

### 6.2 多关键字排序（二级排序）

```c
// 按成绩降序，成绩相同按学号升序
int cmp_score_then_id(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;

    if (sa->score != sb->score)
        return sb->score - sa->score;  // 一级：成绩降序
    return sa->id - sb->id;            // 二级：学号升序
}

// 按成绩降序，成绩相同按姓名字典序
int cmp_score_then_name(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;

    if (sa->score != sb->score)
        return sb->score - sa->score;
    return strcmp(sa->name, sb->name);  // strcmp 直接返回 int
}
```

### 6.3 结构体含浮点数

```c
typedef struct {
    char name[50];
    double gpa;
} Student2;

int cmp_gpa_desc(const void *a, const void *b) {
    Student2 *sa = (Student2 *)a;
    Student2 *sb = (Student2 *)b;
    // 浮点数不能用减法，用比较
    if (sa->gpa > sb->gpa) return -1;  // 降序
    if (sa->gpa < sb->gpa) return 1;
    return 0;
}
```

---

## 七、字符串排序

### 7.1 二维字符数组排序

```c
char str[100][50];  // 最多 100 个字符串，每个最长 49 字符

// 按字典序升序（用 strcmp）
int cmp_str_2d(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

qsort(str, n, sizeof(str[0]), cmp_str_2d);
```

> **理解为什么这样写：** `qsort` 传给 cmp 的是两个元素的地址。每个元素是 `char[50]` 数组。所以 a 的类型是 `char (*)[50]`，但 `strcmp` 的参数类型是 `const char *`，而 `(char *)a` 正好就是该字符串的首地址。所以这样写是对的。

### 7.2 按字符串长度排序

```c
int cmp_str_len(const void *a, const void *b) {
    char *sa = (char *)a;
    char *sb = (char *)b;
    int len_a = strlen(sa);
    int len_b = strlen(sb);
    return len_a - len_b;   // 按长度升序
}

// 长度相同再按字典序：
int cmp_str_len_then_lex(const void *a, const void *b) {
    char *sa = (char *)a;
    char *sb = (char *)b;
    int len_a = strlen(sa);
    int len_b = strlen(sb);
    if (len_a != len_b)
        return len_a - len_b;
    return strcmp(sa, sb);
}
```

### 7.3 指针数组（字符串数组）

```c
char *str_arr[] = {"banana", "apple", "cherry", "date"};

// 按字典序升序
int cmp_str_ptr(const void *a, const void *b) {
    // a 是 "char *" 的地址，即 char**
    char *sa = *(char **)a;   // 解引用拿到 char*
    char *sb = *(char **)b;
    return strcmp(sa, sb);
}

int n = sizeof(str_arr) / sizeof(str_arr[0]);
qsort(str_arr, n, sizeof(char *), cmp_str_ptr);
// 结果：{"apple", "banana", "cherry", "date"}
```

> **⚠️ 新手最容易犯的错误：** 对于 `char *str_arr[]`，cmp 里写 `(char *)a` 是**错的**！
> - a 是 `char **` 类型（指向指针的指针）
> - `(char *)a` 取到的是指针变量本身的地址，而不是字符串首地址
> - 正确写法：`*(char **)a` 先转成 `char**`，再解引用拿到 `char*`

**用图和代码对比：**

```
错误写法：
    a = 0x100  (保存着 str_arr[0] 的地址)
    (char *)a = (char *)0x100 ❌ 这是地址值本身，不是字符串！

正确写法：
    a = 0x100  (str_arr[0] 的地址)
    *(char **)a = str_arr[0] = "banana" ✅ 这才是字符串指针本身！
```

### 7.4 按字符串中数字排序

```c
// 假设字符串格式如 "abc123def45"，提取其中的数字
int extract_num(const char *s) {
    int num = 0;
    while (*s) {
        if (*s >= '0' && *s <= '9')
            num = num * 10 + (*s - '0');
        s++;
    }
    return num;
}

int cmp_str_num(const void *a, const void *b) {
    char *sa = *(char **)a;
    char *sb = *(char **)b;
    return extract_num(sa) - extract_num(sb);
}
```

---

## 八、指针数组排序

### 8.1 结构体指针数组

```c
typedef struct {
    int x, y;
} Point;

Point *ptrs[100];  // 指针数组

// 按点的 x 坐标排序
int cmp_point_ptr(const void *a, const void *b) {
    Point *pa = *(Point **)a;   // 注意：双重指针，先转再解引用
    Point *pb = *(Point **)b;
    return pa->x - pb->x;
}

qsort(ptrs, n, sizeof(Point *), cmp_point_ptr);
```

### 8.2 为什么指针数组的 cmp 要写 `**`

```
内存布局：
ptrs = [0x100] [0x200] [0x300] ...
         ↓       ↓       ↓
       点1     点2     点3

qsort 传给 cmp 两个地址：
  a = &ptrs[0]  = 0x... (指向 ptrs[0] 的地址)
  b = &ptrs[1]  = 0x...

所以：
  *(Point **)a = ptrs[0] = 0x100  → 点1的指针
  *(*(Point **)a)  = 点1 本身
  (*(Point **)a)->x  → 点1的x坐标
```

---

## 九、降序与复杂规则

### 9.1 万能的降序写法

```c
// 升序：a - b
// 降序：b - a

// int 降序
int cmp_int_desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

// 结构体双关键字降序（成绩降序，学号降序）
int cmp_score_id_desc(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    if (sa->score != sb->score)
        return sb->score - sa->score;  // 成绩降序
    return sb->id - sa->id;            // 学号降序
}
```

### 9.2 先按某种规则排，再按另一种排

```c
// 学生：先按成绩分档（优秀>90，及格60-90，不及格<60）
// 同档内按学号升序
int cmp_grade_level(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;

    int level_a = (sa->score >= 90) ? 0 : (sa->score >= 60) ? 1 : 2;
    int level_b = (sb->score >= 90) ? 0 : (sb->score >= 60) ? 1 : 2;

    if (level_a != level_b)
        return level_a - level_b;   // 先按档次
    return sa->id - sb->id;          // 同档按学号排
}
```

### 9.3 自定义优先级（比如牌面排序）

```c
// 扑克牌排序：3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A < 2
int card_value(char card) {
    switch (card) {
        case '3': return 1;
        case '4': return 2;
        case '5': return 3;
        case '6': return 4;
        case '7': return 5;
        case '8': return 6;
        case '9': return 7;
        case 'J': return 8;
        case 'Q': return 9;
        case 'K': return 10;
        case 'A': return 11;
        case '2': return 12;
        default: return 0;
    }
}

int cmp_card(const void *a, const void *b) {
    // 注意：这里 a, b 是 char，但为了统一性用 void*
    return card_value(*(char *)a) - card_value(*(char *)b);
}
```

---

## 十、bsearch 二分查找

与 qsort 配套的二分查找函数，**必须先在有序数组上使用**。

### 10.1 函数原型

```c
void *bsearch(const void *key,      // 待查找的值
              const void *base,     // 数组首地址
              size_t nmemb,         // 元素个数
              size_t size,          // 每个元素大小
              int (*cmp)(const void *, const void *)  // 比较函数
              );
```

### 10.2 使用示例

```c
int a[] = {1, 3, 5, 7, 9, 11, 13};
int n = sizeof(a) / sizeof(a[0]);
int key = 7;

// 先用 qsort 排序（已经是升序了，跳过）
int *result = (int *)bsearch(&key, a, n, sizeof(int), cmp_int);

if (result != NULL)
    printf("找到：%d\n", *result);   // 找到：7
else
    printf("未找到\n");
```

### 10.3 bsearch 的 cmp 写法

```c
// bsearch 的 cmp 和 qsort 的 cmp 可以共用！
// 唯一区别：bsearch 的第一个参数是 key，第二个才是数组元素

// 对于结构体，按 id 查找：
Student stu[100];
// ... 按 id 排序后 ...
int target_id = 1001;
Student *found = (Student *)bsearch(&target_id, stu, n, sizeof(Student),
    cmp_by_id);  // 直接用之前写好的
```

---

## 十一、常考题型

### 题型 1：填写 cmp 函数 ⭐⭐

**题目：** 对 `int a[100]` 按降序排序，补全 cmp 函数。

```c
int cmp(const void *a, const void *b) {
    // 填空：
    return _________________;
}
```

**答案：** `*(int *)b - *(int *)a`

---

### 题型 2：结构体二级排序 ⭐⭐⭐

**题目：** 有学生结构体 `{id, name, score}`，要求按成绩从高到低，成绩相同按姓名字典序从小到大。

```c
int cmp_stu(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    if (sa->score != sb->score)
        return sb->score - sa->score;   // 成绩降序
    return strcmp(sa->name, sb->name);   // 姓名升序（strcmp 就是升序）
}
```

---

### 题型 3：区间排序 ⭐⭐⭐

**题目：** 给定 `int intervals[][2]`，按右端点升序排序。

```c
int cmp_interval(const void *a, const void *b) {
    int *ia = (int *)a;
    int *ib = (int *)b;
    return ia[1] - ib[1];
}
```

---

### 题型 4：字符串指针数组排序 ⭐⭐⭐⭐⭐

**题目：** 对 `char *words[] = {"banana", "apple", "cherry"}` 排序，写 cmp 函数。

```c
int cmp_words(const void *a, const void *b) {
    // a 是 char**
    return strcmp(*(char **)a, *(char **)b);
}
```

> 注意：**不是** `strcmp((char *)a, (char *)b);`，那是二维数组的写法！

---

### 题型 5：判断 cmp 写法的正误 ⭐⭐⭐

**题目：** 以下哪个 cmp 能正确对 `double a[]` 升序排序？

A. `return *(double *)a - *(double *)b;`
B. `return *(double *)a > *(double *)b ? 1 : -1;`
C. `double d = *(double *)a - *(double *)b; return d > 0 ? 1 : (d < 0 ? -1 : 0);`

**答案：** B 和 C 都可以。A 不行，因为差值被截断为 int。

---

### 题型 6：排序稳定性相关 ⭐⭐

**题目：** qsort 是稳定排序吗？

**答案：** **不是。** qsort 底层是快排（有交换），一般是不稳定的。

如果需要稳定排序，用 `mergesort`（某些系统有），或者手动加一个"第二关键字"是原下标的字段。

---

## 十二、速查表

### 12.1 常见类型速查

| 要排序的类型 | cmp 写法 | 调用 qsort |
|-------------|---------|-----------|
| `int a[]` | `return *(int*)a - *(int*)b;` | `qsort(a, n, sizeof(int), cmp);` |
| `float a[]` | 用比较，不可用减法 | 同上 |
| `double a[]` | 用比较，不可用减法 | 同上 |
| `char a[]` | `return *(char*)a - *(char*)b;` | `qsort(a, n, sizeof(char), cmp);` |
| `long long a[]` | 用比较，不可用减法 | `qsort(a, n, sizeof(long long), cmp);` |
| `char a[][N]` | `return strcmp((char*)a, (char*)b);` | `qsort(a, n, sizeof(a[0]), cmp);` |
| `char *a[]` | `return strcmp(*(char**)a, *(char**)b);` | `qsort(a, n, sizeof(char*), cmp);` |
| `struct S a[]` | 转成 `S*` 再比 | `qsort(a, n, sizeof(S), cmp);` |
| `int a[][2]` | 转成 `int*` 再比 | `qsort(a, n, sizeof(a[0]), cmp);` |
| `S *a[]` | 转成 `S**` 再解引用比 | `qsort(a, n, sizeof(S*), cmp);` |

### 12.2 升降序规则

```c
// 升序（从小到大）：
return *(int *)a - *(int *)b;    // a - b

// 降序（从大到小）：
return *(int *)b - *(int *)a;    // b - a

// strcmp 本身就是升序（字典序）：
return strcmp(sa, sb);           // 升序
return strcmp(sb, sa);           // 降序
```

### 12.3 常见错误

| 错误写法 | 场景 | 问题 |
|---------|------|------|
| `return *(double*)a - *(double*)b;` | double 排序 | 结果被截断为 int |
| `return strcmp((char*)a, (char*)b);` | `char *a[]` 排序 | 应该用 `*(char**)a` |
| `return a->score - b->score;` | 没做类型转换 | 忘了 `(Student *)a` |
| 忘记传递 `sizeof` | 任何数组 | qsort 不知道每个元素多大 |
| 元素个数算错 | 任何数组 | `sizeof(a)/sizeof(a[0])` 必须正确 |

### 12.4 万能模板（直接复制改写）

```c
#include <stdlib.h>
#include <string.h>

// ───── 基本类型 ─────

// int 升序
int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// int 降序
int cmp_int_desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

// double 升序
int cmp_double(const void *a, const void *b) {
    double va = *(double *)a, vb = *(double *)b;
    return (va > vb) - (va < vb);  // 技巧：用 bool 差替代三路比较
}

// ───── 二维数组（区间） ─────

// 按第一列升序
int cmp_2d_col0(const void *a, const void *b) {
    return ((int *)a)[0] - ((int *)b)[0];
}

// ───── 结构体 ─────

typedef struct {
    int id;
    char name[50];
    int score;
} Student;

// 成绩降序，成绩相同按学号升序
int cmp_student(const void *a, const void *b) {
    Student *sa = (Student *)a, *sb = (Student *)b;
    if (sa->score != sb->score)
        return sb->score - sa->score;
    return sa->id - sb->id;
}

// ───── 字符串 ─────

// 二维字符数组
int cmp_str2d(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

// 字符指针数组
int cmp_strptr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

// ───── 调用方法 ─────

// int arr[100]; int n = ...;
// qsort(arr, n, sizeof(int), cmp_int);
//
// Student stu[100]; int n = ...;
// qsort(stu, n, sizeof(Student), cmp_student);
//
// char words[100][50]; int n = ...;
// qsort(words, n, sizeof(words[0]), cmp_str2d);
//
// char *ptrs[100]; int n = ...;
// qsort(ptrs, n, sizeof(char *), cmp_strptr);
```

### 12.5 面试/考试口诀

```
qsort 写 cmp，三步要记清：
一接 void*，强转为实际类型
解引用拿到值，比较得负数零正数
负前正后要牢记，升序 a-b 降序 b-a

浮点数不能减，用比较代替
字符串用 strcmp，指针数组要双层
二级排序分层次，先比主要再比次要

二分查找 bsearch，配合同一个 cmp
记得先排序，后查找
```
