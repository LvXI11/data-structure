int partition(int arr[], int low, int high){
    int x = arr[low];
    
    while(low < high){
        while(low < high && arr[high] >= x) high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= x) low++;
        arr[high] = arr[low];
    }
    arr[low] = x;
    return low;
}

void quick_sort(int arr[], int low, int high){
    if(low >= high) return;
    int pivot = partition(arr, low, high);
    quick_sort(arr, low, pivot - 1);
    quick_sort(arr, pivot + 1, high);
}