#include<stdlib.h>

void radix_sort(int* a, int n){
    if(n <= 1) return;
    int* temp = (int*)malloc(sizeof(int) * n);
    if(temp == NULL) return;
    //找最大以确定要处理多少位
    int max = a[0];
    for(int i = 0;i < n; i++) if(a[i] > max) max = a[i];

    for(int exp = 1;max / exp > 0; exp *= 10){
        int cnt[10] = {0};
        //计算每个桶中的元素个数
        for(int i = 0;i < n; i++){
            int d = (a[i] / exp) % 10;
            cnt[d]++;
        }
        //计算前缀和（即确定每个桶中的元素放数组中的哪个区域（下标区域））
        for(int i = 1;i < n; i++){
            cnt[i] += cnt[i - 1];
        }
        //倒着装，确保原数组中的各元素之间的相对顺序不变
        for(int i = n - 1;i >= 0; i--){
            int d = (a[i] / exp) % 10;
            temp[--cnt[d]] = a[i];
        }

        for(int i = 0;i < n; i++){
            a[i] = temp[i];
        }
    }
    free(temp);
}