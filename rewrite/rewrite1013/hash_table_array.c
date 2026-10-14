#include<stdbool.h>
#include<stdio.h>

#define SIZE 11

int table[SIZE];
int seen[SIZE] = {0};

bool insert(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    int emptypos = -1;
    for(int i = 0;i < SIZE; i++){
        if(seen[pos] == 1 && table[pos] == val) return false;
        if(seen[pos] == 0 || seen[pos] == 2){
            emptypos = pos;
            break;
        }
        pos = (pos + 1) % SIZE;
    }
    if(emptypos == -1) return false;
    table[emptypos] = val;
    seen[emptypos] = 1;
    return true;
}

bool delete_value(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    for(int i = 0;i < SIZE; i++){
        if(seen[pos] == 1){
            if(table[pos] == val){
                seen[pos] = 2;
                return true;
            }
        }
        pos = (pos + 1) % SIZE;
    }
    return false;
}

int search(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    for(int i = 0;i < SIZE; i++){
        if(seen[pos] == 1){
            if(table[pos] == val){
                return pos;
            }
        }
        pos = (pos + 1) % SIZE;
    }
    return -1;
}