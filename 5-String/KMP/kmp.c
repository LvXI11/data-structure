#include<stdio.h>
#include<string.h>

int same(char p[],int j,int k){
    for(int t=0;t<k;t++){
        if(p[t]!=p[j-k+t])return 0;
    }
    return 1;
}

void get_next(char p[],int next[]){
    int n=strlen(p);
    next[0]=0;

    for(int j=1;j<n;j++){
        int k=j-1;  //最长公共前后缀长度
        while(k>0&&!same(p,j,k))k--;
        next[j]=k;
    }
}

int kmp(char s[],char p[],int next[]){
    int m=strlen(s);
    int n=strlen(p);
    int i=0;
    int j=0;
    int cmp=0;

    while(i<m&&j<n){
        cmp++;
        if(s[i]==p[j]){
            i++;
            j++;
        }
        else if(j==0) i++;
        else j=next[j];
    }
    printf("kmp比较次数:%d",cmp);
    if(j==n)return i-j;
    return -1;
}

int main(void){
    char s[] = "abababc";
    char p[] = "ababc";
    int next[100];
    get_next(p, next);

    printf("next = ");
    for(int i = 0; i < 5; i++) printf("%d ", next[i]);   // 0 0 0 1 2
    printf("\n");

    printf("结果 = %d\n", kmp(s, p, next));              // 2
    return 0;
}