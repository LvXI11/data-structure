#include<stdbool.h>
#include<stdio.h>

#define SIZE 11

int table[SIZE];
int seen[SIZE] = {0};

bool insert(int val){
    int pos = val % SIZE;
    if(seen[pos] == 0){
        table[pos] = val;
        seen[0] = 1;
        return true;
    }

    int emptypos = (pos + 1) % SIZE;
    int count = 0;
    while(count < SIZE - 1){
        if(seen[emptypos] == 0){
            table[emptypos] = val;
            seen[emptypos] = 1;
            return true;
        }
        emptypos = (emptypos + 1) % SIZE;
        count++;
    }
    return false;
}

bool delete_value(int val){
    int pos = val % SIZE;
    if(seen[pos] == 0) return false;
    int count = 0;
    while(count < SIZE - 1){
       if(table[pos] == val){
        seen[pos] = 0;
        return true;
       }
       pos++;
       count++;
    }
    return false;
}

int search(int val){
    int pos = val % SIZE;
    if(seen[pos] == 0) return -1;
    int count = 0;
    while(count < SIZE - 1){
        if(table[pos] == val) return pos;
        pos++;
        count++;
    }
    return -1;
}