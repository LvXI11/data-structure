#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct SQList{
    int* data;
    int size;
    int capacity;
}SQList;

void init(SQList* L) {
    L->data = (int*)malloc(sizeof(int) * 10);
    L->capacity = 10;
    L->size = 0;
}

bool extendCapacity(SQList* L) {
    int* temp = realloc(L->data, sizeof(int) * L->capacity * 2);
    if(temp == NULL) return false;
    L->data = temp;
    L->capacity *= 2;
    return true;
}
bool insert(SQList* L, int val, int pos) {
    if(L->size == L->capacity) if(!extendCapacity(L)) return false;
    if(pos < 0 || pos > L->size) return false;
    for(int i = L->size;i > pos; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[pos] = val;
    L->size++;
    return true;
}

bool delete_elem(SQList* L, int pos) {
    if(L->size == 0) return false;
    if(pos < 0 || pos > L->size - 1) return false;
    for(int i = pos;i < L->size - 1; i++) {
        L->data[i] = L->data[i + 1];
    }
    L->size--;
    return true;
}

int find(SQList* L, int val) {
    for(int i = 0;i < L->size; i++) {
        if(L->data[i] == val) return i;
    }
    return -1;
}

void print(SQList* L) {
    for(int i = 0;i < L->size; i++) {
        printf("%d ", L->data[i]);
    }
}

int main(void) {
    SQList L;
    init(&L);
    for (int i = 1; i <= 5; i++) insert(&L, i, L.size);   // 1 2 3 4 5
    insert(&L, 9, 1);                                      // 1 9 2 3 4 5
    print(&L); printf("\n");
    delete_elem(&L, 0);
    print(&L); printf("\n");
    for (int i = 0; i < 30; i++) insert(&L, i, L.size);    // ← 逼扩容，暴露 realloc
    printf("size=%d capacity=%d\n", L.size, L.capacity);
    return 0;
}