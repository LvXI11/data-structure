#include<stdio.h>

int binarySearch(int a[], int n, int target) {
    int l = 0; int r = n - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(a[mid] == target) return mid;
        else if(a[mid] < target) {
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    return -1;
}