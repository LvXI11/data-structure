#include<stdio.h>
#include<stdbool.h>

typedef struct Stack{
    char elem;
    struct Stack* next;
}Stack;

void push_elem(Stack* S,char elem){

}

bool pop_elem(Stack* S,char* elem){

}

bool is_empty(Stack* S){
    return S->next==NULL;
}

int main(void){
    Stack* S;
    char ch;
    bool matched=true;
    while((ch=getchar())&&ch!='\n'&&ch!=EOF){
        if(ch=='('||ch=='['||ch=='{')push_elem(S,ch);
        else if(ch==')'||ch=='}'||ch==']'){
        char rec;
        bool ok=pop_elem(S,&rec)&&
               (ch==')'&&rec=='('
                ||ch==']'&&rec=='['
               ||ch=='}'&&rec=='{');
        if(!ok){
            matched=false;
            break;
        }
        }
    }
    if(is_empty(S)&&matched)printf("合法\n");
    else printf("非法\n");
    return 0;
}