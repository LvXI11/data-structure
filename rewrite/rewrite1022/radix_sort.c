#include<stdlib.h>
#include<stdio.h>


void radix_sort(int* arr, int n) {
    if(n <= 1) return;
    int* temp = (int*)malloc(sizeof(int) * n);
    if(!temp) return;

    int max = arr[0];
    for(int i = 0;i < n; i++) if(arr[i] > max) max = arr[i];

    for(int exp = 1;max / exp > 0; exp *= 10) {
        int bucket[10] = {0};

        for(int i = 0;i < n; i++) {
            int d = arr[i] / exp % 10;
            bucket[d]++;
        }

        for(int i = 1;i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }

        for(int i = n - 1;i >= 0; i--) {
            int d = arr[i] / exp % 10;
            temp[--bucket[d]] = arr[i];
        }

        for(int i = 0;i < n; i++) {
            arr[i] = temp[i];
        }
    }
    free(temp);
}

int main(void) {
    int a[] = {53, 3, 542, 748, 14, 214, 154, 63, 616, 589};
    for(int i = 0;i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    radix_sort(a, 10);
    for(int i = 0;i < 10; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}