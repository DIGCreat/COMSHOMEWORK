#include<stdio.h>
#include<stdlib.h>
#include "test2.h"

int main(void)
{
    int num1, num2;
    num1 = 2;
    num2 = 3;
    printf("the sum of %d + %d is %d\n", num1, num2, add(num1, num2));
    exit(0);
}
