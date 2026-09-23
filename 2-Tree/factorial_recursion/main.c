#include<stdio.h>
int factorial_recursion(int num){
    if(num==1) return 1;
    else return num*factorial_recursion(num-1);
}
int main(void){
    int num=4;
    printf("%d\n",factorial_recursion(num));
    return 0;
}