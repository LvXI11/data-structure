#include<stdio.h>
#include<stdlib.h>

void radix_sort(int* a, int n) {
    if(n == 1 || n== 0) return;
    int* tmp = (int*)malloc(sizeof(int) * n);
    
    int max = a[0];
    for(int i = 0;i < n; i++) if(max < a[i]) max = a[i];

    for(int exp = 1;max / exp >= 1; exp *= 10) {
        int bucket[10] = {0};

        for(int i = 0;i < n; i++) {
            int  d = a[i] / exp % 10;
            bucket[d]++;
        }

        for(int j = 1;j < 10; j++) {
            bucket[j] += bucket[j - 1];
        }

        for(int k = n - 1;k >= 0; k--) {
            int d = a[k] / exp % 10;
            tmp[--bucket[d]] = a[k];
        }

        for(int m = 0;m < n; m++) {
            a[m] = tmp[m];
        }
    }

    free(tmp);
}