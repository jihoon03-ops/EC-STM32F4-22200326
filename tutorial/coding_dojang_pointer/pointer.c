#include <stdio.h>

int main() {

    int x = 10;
    double y = 2.5;
    int* ptrX = &x;
    double* ptrY = &y;

    /*
    -Print the address of variable ¡®x¡¯
    -Print the address of variable ¡®y¡¯
    -Print the value of pointer ¡®ptrX ¡®
    -Print the address of pointer ¡®ptrX ¡®
    -Print the size of pointer ¡®ptrX ¡®
    */
    printf("%p\n", &x);
    printf("%p\n", &y);
    printf("%p\n", ptrX);
    printf("%p\n", &ptrX);
    printf("%zd\n", sizeof(ptrX));
    /*
    -Print the value of pointer ¡®ptrY ¡®
    -Print the address of pointer ¡®ptrY ¡®
    -Print the size of pointer ¡®ptrY
    */
    printf("%p\n", ptrY);
    printf("%p\n", &ptrY);
    printf("%zd\n", sizeof(ptrY));

}