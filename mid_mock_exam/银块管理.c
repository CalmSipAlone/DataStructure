#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int weigh;
    struct node *next;
} Node;

Node* create_node(int weigh) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->weigh = weigh;
    newnode->next = NULL;
    return newnode;
}

// 将新结点按升序插入有序链表，返回新头
Node* insert_sorted(Node *head, Node *p) {
    if (head == NULL || p->weigh < head->weigh) {
        p->next = head;
        return p;
    }
    Node *cur = head;
    while (cur->next != NULL && cur->next->weigh < p->weigh) {
        cur = cur->next;
    }
    p->next = cur->next;
    cur->next = p;
    return head;
}

int main() {
    int total = 0;
    Node *head = NULL;

    while (1) {
        int weigh;
        scanf("%d", &weigh);
        if (weigh == 999999) break;

        if (weigh > 0) {                     // 购入银块
            total += weigh;
            Node *p = create_node(weigh);
            head = insert_sorted(head, p);
        }
        else if (weigh < 0) {              // 卖出白银
            int m = -weigh;
            if (total < m) continue;         // 总量不足，忽略
            total -= m;

            Node *p = head;
            Node *prev = NULL;
            int cum = 0;

            while (p != NULL) {
                cum += p->weigh;
                if (cum < m) {
                    // 整个取出该银块，删除结点
                    Node *temp = p;
                    p = p->next;
                    if (prev == NULL)
                        head = p;
                    else
                        prev->next = p;
                    free(temp);
                } else if (cum == m) {
                    // 恰好卖完，删除结点后停止
                    Node *temp = p;
                    p = p->next;
                    if (prev == NULL)
                        head = p;
                    else
                        prev->next = p;
                    free(temp);
                    break;
                } else {                     // cum > m，需要切割
                    p->weigh = cum - m;      // 剩余重量放回
                    // 链表仍保持升序：切割后的重量 < 原重量 ≤ 后续所有结点
                    break;
                }
            }
            // 无需排序：删除了前缀最小结点，切割后剩余重量 ≤ 后续所有结点
        }
        else {                             // weigh == 0: 熔合
            Node *p = head;
            Node *prev = NULL;
            int sum_small = 0;

            // 遍历删除所有重量 < 10 的结点，并累计重量
            while (p != NULL) {
                if (p->weigh < 10) {
                    sum_small += p->weigh;
                    Node *temp = p;
                    p = p->next;
                    if (prev == NULL)
                        head = p;
                    else
                        prev->next = p;
                    free(temp);
                } else {
                    prev = p;
                    p = p->next;
                }
            }

            // 将熔合后的银块按升序插入
            if (sum_small > 0) {
                Node *q = create_node(sum_small);
                head = insert_sorted(head, q);
            }
        }
    }

    // 输出结果
    Node *p = head;
    while (p != NULL) {
        printf("%d ", p->weigh);
        p = p->next;
    }

    return 0;
}