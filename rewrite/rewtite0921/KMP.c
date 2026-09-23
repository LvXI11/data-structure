#include<stdio.h>
#include<string.h>

int same(char p[],int j,int k){
    for(int t=0;t<k;t++){
        if(p[t]!=p[j-k+t])return 0;
    }
    return 1;
}
//暴力算法，复杂度为O(n^2)
void get_next_brute(char p[],int next[]){
    int n=strlen(p);
    next[0]=0;
    for(int j=1;j<n;j++){
        int k=j-1;
        while(k>0&&!same(p,j,k)) k--;
        next[j]=k;
    }
}
//递推算法，复杂度为O(n)
void get_next(char p[],int next[]){
    int n=strlen(p);

    if(n==0)return; 
    next[0]=0;
    if(n==1)return;
    next[1]=0;

    int k=0;
    for(int j=2;j<n;j++){
        while(k>0&&p[j-1]!=p[k]) k=next[k];

        if(p[j-1]==p[k])k++;
        next[j]=k;
    }
}

int kmp(char s[],char p[],int next[]){
    int m=strlen(s);
    int n=strlen(p);
    int i=0; int j=0; int cmp=0;

    while(i<m&&j<n){
        cmp++;
        if(s[i]==p[j]){
            i++;
            j++;
        }
        else if(j==0) i++;
        else {
            j=next[j];
        }

        if(j==n) return i-j;
    }
    return -1;
}