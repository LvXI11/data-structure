#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    char data[50];
    int top;
}Stack;

void init_stack(Stack* S) {S->top=-1;}
void push(Stack* S,char e) {S->data[++S->top]=e;}
void pop(Stack* S,char* rec) {if(S->top==-1)return; *rec=S->data[S->top--];}

int priority(char op){
    if(op=='*'||op=='/') return 2;
    if(op=='+'||op=='-') return 1;
    return 0;
}

void infix_to_postfix(char s[],char out[]){
    Stack S;
    init_stack(&S);
    int k=0;

    for(int i=0;s[i]!='\0';i++){
        char ch=s[i];
        if(ch>='0'&&ch<='9'){
            out[k++]=ch;
        }
        else if(ch=='('){
            push(&S,ch);
        }
        else if(ch==')'){
            char t;
            while(1){
                pop(&S,&t);
                if(t=='(')break;
                out[k++]=t;
            }
        }
        else{
            char t;
            while(S.top!=-1&&priority(S.data[S.top])>=priority(ch)){
                pop(&S,&t);
                out[k++]=t;
            }
            push(&S,ch);
        }
    }
    while(S.top!=-1){
        char t;
        pop(&S,&t);
        out[k++]=t;
    }
    out[k]='\0';
}

int eval_postfix(char s[]){
    int st[100];
    int top=-1;

    for(int i=0;s[i]!='\0';i++){
        char ch=s[i];

        if(ch>='0'&&ch<='9'){
            st[++top]=ch-'0';
        }
        else{
            int r=st[top--];
            int l=st[top--];

            int v;
            if(ch=='+') v=l+r;
            else if(ch=='-') v=l-r;
            else if(ch=='*') v=l*r;
            else v=l/r;
            st[++top]=v;
        }
    }
    return st[top];
}

int main(void)
{
    char *infix[] = { "3+4*2", "3*(7-2)", "3-2+4", "(1+2)*(3+4)" };
    int   want[]  = {  11,      15,       5,       21 };

    for(int i = 0; i < 4; i++){
        char out[100];
        infix_to_postfix(infix[i], out);       /* 中缀 → 后缀 */

        int v = eval_postfix(out);             /* 后缀 → 求值 */

        printf("%-12s -> %-9s -> %3d   应该 %3d   %s\n",
               infix[i], out, v, want[i], v == want[i] ? "OK" : "!! 错");
    }
    return 0;
}