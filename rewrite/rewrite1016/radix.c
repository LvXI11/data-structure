#include<stdlib.h>
#include<stdio.h>

void radix_sort(int* arr, int n){
    if(n <= 1) return;

    int max = arr[0];
    for(int i = 1;i < n; i++) if(arr[i] > max) max = arr[i];

    int* temp = (int*)malloc(sizeof(int) * n);
    if(!temp) return;

    for(int exp = 1;max / exp > 0; exp *= 10){
        int cnt[10] = {0};

        for(int i = 0;i < n; i++){
            int d = (arr[i] / exp) % 10;
            cnt[d]++;
        }
    
        for(int i = 1;i < 10; i++){
            cnt[i] += cnt[i - 1];
        }

        for(int t = n - 1;t >= 0; t--){
            int d = (arr[t] / exp) % 10;
            temp[--cnt[d]] = arr[t];
        }

        for(int t = 0;t < n; t++){
            arr[t] = temp[t];
        }
    }
    free(temp);
}