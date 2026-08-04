# Day 21: Common Sorting Algorithms | 常见排序算法

> A bilingual (English / 中文) walkthrough of Day 21.
> 本节为第二十一天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Sorting arranges elements of a collection in a defined order (ascending or descending). This day begins implementing common comparison-based sorting algorithms, starting with **Bubble Sort**, and lists a roadmap of what to study next.

**中文**

排序将集合中的元素按某种顺序（升序或降序）排列。本节开始实现常见的基于比较的排序算法，从**冒泡排序**入手，并列出后续学习路线图。

---

## 2. Sorting Algos Checklist | 排序算法清单

- [x] Bubble Sort | 冒泡排序
- [ ] Insertion Sort | 插入排序
- [ ] Selection Sort | 选择排序
- [ ] Merge Sort | 归并排序
- [ ] Quick Sort | 快速排序
- [ ] Heap Sort | 堆排序

---

## 3. Bubble Sort | 冒泡排序

```c
#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int A[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
}

int main()
{
    int A[] = {12, 11, 3, 6, 9, 15, 7, 5, 2, 1}, n = 10;
    bubbleSort(A, n);
    for (int i = 0; i < 10; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
```

**English**
- Repeatedly steps through the list, compares adjacent elements, and **swaps** them if they are in the wrong order.
- After each outer pass, the largest unsorted element **bubbles up** to its correct position at the end, so the inner loop can stop `i` elements earlier.
- Complexity:
  - **Worst/Average case**: O(n²)
  - **Best case** (already sorted, with an early-exit optimization): O(n)
  - **Space**: O(1) — in-place.
  - **Stable**: yes (equal elements keep their relative order).
- `swap` uses pointers so it modifies the array in place — a nice reminder of Day 10–12's pointer concepts.

**中文**
- 反复遍历数组，比较相邻元素，若顺序错误就**交换**。
- 每一轮外层循环后，最大的未排序元素会**冒泡**到末尾正确位置，因此内层循环可提前 `i` 个元素结束。
- 复杂度：
  - **最坏/平均情况**：O(n²)
  - **最好情况**（已有序且带提前退出优化）：O(n)
  - **空间**：O(1) —— 原地排序。
  - **稳定**：是（相等元素保持相对顺序）。
- `swap` 通过指针实现，原地修改数组 —— 正好回顾了第十至十二天的指针知识。

---

## 4. Complexity Comparison | 复杂度对比

**English**

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

**中文**

| 算法 | 最好 | 平均 | 最坏 | 空间 | 稳定 |
|------|------|------|------|------|------|
| 冒泡排序 | O(n) | O(n²) | O(n²) | O(1) | 是 |
| 插入排序 | O(n) | O(n²) | O(n²) | O(1) | 是 |
| 选择排序 | O(n²) | O(n²) | O(n²) | O(1) | 否 |
| 归并排序 | O(n log n) | O(n log n) | O(n log n) | O(n) | 是 |
| 快速排序 | O(n log n) | O(n log n) | O(n²) | O(log n) | 否 |
| 堆排序 | O(n log n) | O(n log n) | O(n log n) | O(1) | 否 |

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `bubbleSort.c` | Bubble sort implementation | 冒泡排序实现 |
| `day-21-summary.md` | Day 21 notes | 第二十一天学习笔记 |