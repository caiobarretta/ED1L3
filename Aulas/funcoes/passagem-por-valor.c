#include <stdio.h>

int soma(int x, int y)
{
    int z = x + y;

    puts("===> FUNÇÃO");
    printf("&a = %p, a = %d\n", &x, x);
    printf("&b = %p, b = %d\n", &y, y);
    printf("&c = %p, c = %d\n", &z, z);

    return z;
}

int main()
{

    int a = 10;
    int b = 20;
    int c;

    puts("### ANTES DE CHAMAR A FUNÇÃO");
    printf("&a = %p, a = %d\n", &a, a);
    printf("&b = %p, b = %d\n", &b, b);
    printf("&c = %p, c = %d\n", &c, c);

    c = soma(a, b);

    puts("### DEPOIS DE CHAMAR A FUNÇÃO");

    printf("&a = %p, a = %d\n", &a, a);
    printf("&b = %p, b = %d\n", &b, b);
    printf("&c = %p, c = %d\n", &c, c);

    return 0;
}