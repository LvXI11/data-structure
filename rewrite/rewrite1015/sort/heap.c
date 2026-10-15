void sift_down(int arr[], int size,int i){
   while(2 * i + 1 < size){
    int bigger = 2 * i + 1;
    if(2 * i + 2 < size && arr[2 * i + 2] > arr[bigger])
    bigger = 2 * i + 2;
    if(arr[i] >= arr[bigger]) break;
    int temp = arr[i];
    arr[i] = arr[bigger];
    arr[bigger] = temp;
    i = bigger;
   }
}

void build_heap(int arr[], int n){
    for(int i = n / 2 - 1;i >= 0; i--)
    sift_down(arr, n, i);
}

void heap_sort(int arr[], int n){
    build_heap(arr, n);
    for(int end = n - 1;end > 0; end--){
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;
        sift_down(arr, end, 0);
    }
}

