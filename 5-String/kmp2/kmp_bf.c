/* ============================================================
 * get_next_bf —— 暴力求 next 数组
 *
 *   p[]   模式串
 *   next[] 输出数组（调用者分配，长度至少 m）
 *   m     模式串长度
 *
 * 约定：next[0] = -1
 * ============================================================ */

#include<string.h>

void get_next_bf(const char p[], int next[], int m)
{
    next[0] = -1;                        /* 约定：长度 0 的串没有前后缀 */

    for (int j = 1; j < m; j++) {
        /* j 有两重身份：
             ① next 数组的下标（这一轮要填 next[j]）
             ② "前缀的长度" —— 这一格问的是 p[0..j-1] 这 j 个字符
           从 1 开始（next[0] 是约定），到 m-1 结束（真前缀最长 m-1） */

        next[j] = 0;                     /* 先假定"没有相等前后缀"（默认 0） */

        for (int len = j - 1; len >= 1; len--) {
            /* len = 正在试的"相等前后缀长度"候选
               ─ 为什么最大是 j-1？
                 真前后缀不能是整个串，串长是 j，所以最长只能到 j-1
               ─ 为什么从大到小（len--）？
                 第一个配上的一定是最长的 → 可以立刻 break（省掉后面所有尝试） */

            int ok = 1;                  /* 先假设这一段能配上 */

            for (int t = 0; t < len; t++) {
                /* 逐字符比较：前缀第 t 个  vs  后缀第 t 个
                     p[t]             ← 前缀：从下标 0 开始
                     p[j - len + t]   ← 后缀：从下标 (j-len) 开始
                   后缀是"贴在末尾"的，所以起点 = j - len
                   两边都是 +t，所以永远是对齐的第 t 个对第 t 个 */
                if (p[t] != p[j - len + t]) {
                    ok = 0;              /* 有一个字对不上 → 这个 len 作废 */
                    break;               /* 不用再比后面的了 */
                }
            }

            if (ok) {                    /* len 个字符全部对上 */
                next[j] = len;           /* 填进答案 */
                break;                   /* ★ 从大到小试，第一个就是最长的 → 立刻退出 */
            }
        }
    }
}

int kmp_bf(char s[],char p[],int next[]){
    int m = strlen(s);
    int n = strlen(p);
    int i = 0;
    int j = 0;

    int k = -1;
    while(i < m && j < n){
        if(k = -1 || p[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }

    if(j == n) return i-j;
    else return -1;
}