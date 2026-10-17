#include<ctype.h>

static int priority(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

static int cal(int a, int b, int op){
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    return a / b;
}

static int read_number(const char* s, int* i){
    int v = 0;
    while(isdigit((unsigned char)s[*i])) {
        v = v * 10 + (s[*i] - '0');
        (*i)++;
    }
    return v;
}

static void write_number(char* out, int* k, int v){
    char tmp[16]; int t = 0;
    if(v == 0) tmp[t++] = '0';
    while(v > 0) { tmp[t++] = (char)(v % 10 + '0'); v /= 10; }
    while(t > 0) { out[(*k)++] = tmp[--t]; }
    out[(*k)++] = ' '; 
}

void infix_to_postfix(const char* infix, char* out){
    char op[256]; int ot = 0;
    int i = 0; int k = 0;
    op[ot++] = '#';

    while(infix[i] != '\0') {
        char ch = infix[i];
        
        if(ch == ' ') {
            i++;
            continue;
        }

        if(isdigit((unsigned char)ch)) {
            write_number(out, &k, read_number(infix, &i));
            continue;
        }

        if(ch == '(') {
            op[ot++] = '(';
            i++;
            continue;
        }

        if(ch == ')') {
            while(op[ot - 1] != '('){
                out[k++] = op[--ot];
                out[k++] = ' ';
            }
            ot--;
            i++;
            continue;
        }

        while(ot > 1 && priority(op[ot - 1]) >= priority(ch)){
            out[k++] = op[--ot];
            out[k++] = ' ';
        }
        op[ot++] = ch;
        i++;
    }

    while(ot > 1) {
        out[k++] = op[--ot];
        out[k++] = ' ';
    }
    if(k > 1 && out[k - 1] == ' ') k--;
    out[k] = '\0';
}

int evaluate_postfix(const char* postfix){
    int num[256]; int nt = 0;
    int i = 0;
    while(postfix[i] != '\0') {
        char ch = postfix[i];

        if(ch == ' ') {
            i++;
            continue;
        }

        if(isdigit((unsigned char)ch)){
            num[nt++] = read_number(postfix, &i);
            continue;
        }

        char op = ch;
        int b = num[--nt];
        int a = num[--nt];
        num[nt++] = cal(a, b, op);
        i++;
    }
    return num[0];
}

int evaluate(const char* expr){
    char post[256];
    infix_to_postfix(expr, post);
    return evaluate_postfix(post);
}