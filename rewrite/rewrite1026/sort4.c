#include<stdio.h>
#include<stdlib.h>

void shell_sort(int arr[], int n) {
    int gap = n / 2;
    for(;gap >= 1; gap /= 2) {
        for(int i = gap;i < n; i++) {
            int x = arr[i];
            int j = i - gap;
            while(j >= 0 && arr[j] > x) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = x;
        }
    }
}

int partition(int arr[], int low, int high) {
    int x = arr[low];
    while(low < high) {
        while(low < high && arr[high] >= x) high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= x) low++;
        arr[high] = arr[low];
    }
    arr[low] = x;
    return low;
}

void quick_sort(int arr[], int low, int high) {
    if(low >= high) return;
    int pivot = partition(arr, low, high);
    quick_sort(arr, low, pivot - 1);
    quick_sort(arr, pivot + 1, high);

}

void merge(int arr[], int temp[],int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;
    while(i <= mid && j <= high) {
        if(arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while(i <= mid) temp[k++] = arr[i++];
    while(j <= high) temp[k++] = arr[j++];

    for(int t = low;t <= high; t++) {
        arr[t] = temp[t];
    }
}

void merge_sort(int arr[], int temp[], int low, int high) {
    if(low >= high) return;
    int mid = (low + high) / 2;
    merge_sort(arr, temp, low, mid);
    merge_sort(arr, temp, mid + 1, high);
    merge(arr, temp, low, mid, high);
}

void radix_sort(int arr[], int n) {
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
    int src[] = {53, 3, 542, 748, 14, 214, 154, 63, 616, 589};
    for(int i = 0;i < 10; i++) printf("%d ", src[i]);
    printf("\n");

    shell_sort(src, 10);
    for(int i = 0;i < 10; i++) printf("%d ", src[i]);
    printf("\n");

    quick_sort(src, 0, 9);
    for(int i = 0;i < 10; i++) printf("%d ", src[i]);
    printf("\n");

    int temp[10];
    merge_sort(src, temp, 0, 9);
    for(int i = 0;i < 10; i++) printf("%d ", src[i]);
    printf("\n");

    radix_sort(src, 10);
    for(int i = 0;i < 10; i++) printf("%d ", src[i]);
    printf("\n");

    return 0;
}