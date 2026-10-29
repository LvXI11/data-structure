#include<stdio.h>

int seq_search(int a[], int n, int key) {
    for(int i = 0;i < n; i++) {
        if(a[i] == key) return i;
    }
    return -1;
}

int bin_search(int a[], int n, int key) {
    int left = 0;
    int right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(a[mid] == key) return mid;
        if(a[mid] > key) { right = mid - 1; }
        else { left = mid + 1; }
    }
    return -1;
}

int main(void) {
    int a[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = (int)(sizeof(a) / sizeof(a[0]));
    int keys[] = {23, 2, 91, 100, 1};
    int m = (int)(sizeof(keys) / sizeof(keys[0]));

    for (int i = 0; i < m; i++) {
        int k = keys[i];

        int s = seq_search(a, n, k);          // 先存结果
        printf("seq_search %d -> %d\n", k, s);

        int b = bin_search(a, n, k);          // 先存结果
        printf("bin_search %d -> %d\n", k, b);
    }
    return 0;
}