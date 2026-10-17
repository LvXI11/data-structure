#include<stdio.h>
#include<string.h>

int brute_force(char s[],char p[]){
    int cmp=0;
    int m=strlen(s);
    int n=strlen(p);

    for(int i=0;i<=m-n;i++){
        int j=0;
        while(j<n){
            cmp++;
            if(s[i+j]!=p[j]) break;
            j++;
        }
        if(j==n)return i;
    }
    return -1;
} 
int main(void){
    printf("%d\n", brute_force("ababcabcacbab", "abcac"));   // 5
    printf("%d\n", brute_force("abababc", "abc"));           // 4
    printf("%d\n", brute_force("aaaaaaaaab", "aaab"));       // 6
    return 0;
}