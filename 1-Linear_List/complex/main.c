#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct{
    float realpart;
    float imagpart;
}Complex;
void init(Complex* Z,float real,float imag){
    Z->realpart=real;
    Z->imagpart=imag;
}
void add(Complex* Z,Complex A,Complex B){
    Z->realpart=A.realpart+B.realpart;
    Z->imagpart=A.imagpart+B.imagpart;
}
void sub(Complex* Z,Complex A,Complex B){
    Z->realpart=A.realpart-B.realpart;
    Z->imagpart=A.imagpart-B.imagpart;
}
void multiple(Complex* Z,Complex A,Complex B){
    Z->realpart=A.realpart*B.realpart;
    Z->imagpart=A.imagpart*B.imagpart;
}
bool divide(Complex* Z,Complex A,Complex B){
    if(B.realpart==0||B.imagpart==0){
        printf("实部和虚部为零时不能做除数\n");
        return false;
    }
    Z->realpart=A.realpart/B.realpart;
    Z->imagpart=A.imagpart/B.imagpart;
    return true;
}
int main(void){
    Complex z1,z2,z;
    init(&z1,6,8);
    printf("z1=%.2f+%.2fi\n",z1.realpart,z1.imagpart);
    init(&z2,4,3);
    printf("z2=%.2f+%.2fi\n",z2.realpart,z2.imagpart);
    add(&z,z1,z2);
    printf("z1+z2=%.2f+%.2fi\n",z.realpart,z.imagpart);
    sub(&z,z1,z2);
    printf("z1-z2=%.2f+%.2fi\n",z.realpart,z.imagpart);
    multiple(&z,z1,z2);
    printf("z1*z2=%.2f+%.2fi\n",z.realpart,z.imagpart);
    if(divide(&z,z1,z2))
    printf("z1/z2=%.2f+%.2fi\n",z.realpart,z.imagpart);
    system("pause");
    return 0;
}