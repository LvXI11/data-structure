#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

static int priority(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

static int cal(int a, int b, char op) {
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    return a / b;
}

static int readNumber(const char* s, int* i) {
    int v = 0;
    while(isdigit((char)s[*i])) {
        v = v * 10 + s[*i] - '0';
        (*i)++;
    }
    return v;
}

static void writeNumber(char* out, int* k, int v) {
    char tmp[16]; int t = 0;
    if(v == 0) tmp[t++] = '0';
    while(v > 0) { tmp[t++] = (char)(v % 10 + '0'); v /= 10; }
    while(t > 0) { out[*k++] = tmp[--t]; }
    out[*k++] = ' ';
}

void prefixToInfix(const char* prefix, char* out) {
    char op[256]; int ot = 0;
    int i = 0; int k = 0;
    op[ot++] = '#';

    while(prefix[i] != '\0') {
        char ch = prefix[i];

        if(isblank((char)ch)) {
            i++;
            continue;
        }

        if(isdigit((char)ch)) {
            writeNumber(out, &k, readNumber(prefix, &i));
            continue;
        }

        if(ch == '(') {
            op[ot++] = '(';
            i++;
            continue;
        }

        if(ch == ')') {
            while(op[ot - 1] != '(') {
                out[k++] = op[--ot];
                out[k++] = ' ';
            }
            ot--;
            i++;
            continue;
        }

        while(ot > 1 && priority(op[ot - 1]) >= priority(ch)) {
            out[k++] = op[--ot];
            out[k++] = ' ';
        }
        op[ot++] = ch;
    }

    while(ot > 1) {
        out[k++] = op[--ot];
        out[k++] = ' ';
    }
    if(k > 1 && out[k - 1] == ' ') k--;
    out[k] = '\0';
}

int evaluateInfix(const char* infix) {
    int nums[256]; int nt = 0;
    int i = 0;

    while(infix[i] != '\0') {
        char ch = infix[i];

        if(isblank((char)ch)) {
            i++;
            continue;
        }

        if(isdigit((char)ch)) {
            nums[nt++] = readNumber(infix, &i);
            continue;
        }

        int b = nums[nt--];
        int a = nums[nt--];
        nums[nt++] = cal(a, b, ch);
        i++;
    }
    return nums[0];
}

int expression(const char* expression) {
    char out[256];
    prefixToInfix(expression, out);
    return evaluateInfix(out);
}