#include <stdio.h>

// args는 고정 매개변수
void printNumbers(int args, ...)
{
    printf("%d ", args);
}

int main()
{
    printNumbers(10, 10);
    printNumbers(20, 10, 20);
    printNumbers(30, 10, 20, 30);
    printNumbers(40, 10, 20, 30, 40);

    return 0;
}
