/* 自测驱动（AI 维护，勿改）
 * 用法：把它和你的 sort8.c 放同一目录，然后
 *   gcc -Wall -Wextra -o _driver_sort8.exe _driver_sort8.c
 *   _driver_sort8.exe
 * 它会把你的每个排序和标准库 qsort 对答案。
 */
#include "sort8.c"
#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

static int pass = 0, fail = 0;

static void run(const char *name, void (*fn)(int *, int),
                const int *data, int n, const char *tag) {
    int cap = (n > 0) ? n : 1;
    int *a = (int *)malloc(sizeof(int) * cap);
    int *e = (int *)malloc(sizeof(int) * cap);
    for (int i = 0; i < n; i++) { a[i] = data[i]; e[i] = data[i]; }
    qsort(e, n, sizeof(int), cmp_int);

    fn(a, n);

    int ok = 1;
    for (int i = 0; i < n; i++) { if (a[i] != e[i]) { ok = 0; break; } }
    if (ok) pass++; else fail++;
    printf("  %-12s n=%-3d %-10s %s\n", name, n, tag, ok ? "OK" : "<<<< 不对");

    if (!ok) {
        printf("      输入: "); for (int i = 0; i < n && i < 12; i++) printf("%d ", data[i]); printf(n > 12 ? "...\n" : "\n");
        printf("      期望: "); for (int i = 0; i < n && i < 12; i++) printf("%d ", e[i]);    printf(n > 12 ? "...\n" : "\n");
        printf("      实际: "); for (int i = 0; i < n && i < 12; i++) printf("%d ", a[i]);    printf(n > 12 ? "...\n" : "\n");
    }
    free(a); free(e);
}

#define N 30

static void build(int *buf, int n, int mode) {   /* mode: 0随机 1升序 2降序 3全同 */
    for (int i = 0; i < n; i++) {
        if (mode == 0)      buf[i] = rand() % 1000;
        else if (mode == 1) buf[i] = i * 7;
        else if (mode == 2) buf[i] = (n - i) * 7;
        else                buf[i] = 42;
    }
}

/* 非负数据（基数排序用） */
static void build_pos(int *buf, int n, int mode) {
    for (int i = 0; i < n; i++) {
        if (mode == 0)      buf[i] = rand() % 100000;
        else if (mode == 1) buf[i] = i * 13;
        else if (mode == 2) buf[i] = (n - i) * 13;
        else                buf[i] = 7;
    }
}

static void all_cases(const char *name, void (*fn)(int *, int)) {
    int buf[N] = {0};
    printf("-- %s --\n", name);
    run(name, fn, buf, 0, "空数组");
    build(buf, 1, 0);  run(name, fn, buf, 1,  "单元素");
    build(buf, 2, 2);  run(name, fn, buf, 2,  "两元素逆序");
    build(buf, N, 0);  run(name, fn, buf, N,  "随机");
    build(buf, 10, 1); run(name, fn, buf, 10, "已升序");
    build(buf, 10, 2); run(name, fn, buf, 10, "已降序");
    build(buf, 8, 3);  run(name, fn, buf, 8,  "全相同");
    printf("\n");
}

static void all_cases_pos(const char *name, void (*fn)(int *, int)) {
    int buf[N] = {0};
    printf("-- %s --\n", name);
    run(name, fn, buf, 0, "空数组");
    build_pos(buf, 1, 0);  run(name, fn, buf, 1,  "单元素");
    build_pos(buf, N, 0);  run(name, fn, buf, N,  "随机");
    build_pos(buf, 10, 1); run(name, fn, buf, 10, "已升序");
    build_pos(buf, 10, 2); run(name, fn, buf, 10, "已降序");
    build_pos(buf, 8, 3);  run(name, fn, buf, 8,  "全相同");
    printf("\n");
}

int main(void) {
    srand(20261015);
    printf("===== 8 种排序 · 黑盒对答案（标准库 qsort 作参照）=====\n\n");
    all_cases("冒泡", bubble_sort);
    all_cases("选择", select_sort);
    all_cases("插入", insert_sort);
    all_cases("希尔", shell_sort);
    all_cases("快速", quick_sort);
    all_cases("归并", merge_sort);
    all_cases("堆",   heap_sort);
    all_cases_pos("基数（非负）", radix_sort);

    printf("================\n");
    printf("通过 %d / %d%s\n", pass, pass + fail, fail == 0 ? "   ★ 全过" : "   ✗ 有挂的");
    return fail == 0 ? 0 : 1;
}
