#include <stdio.h>

union s
{
    char a1;
    int a2;
    double s;
};

int main()
{
    union s k = {'1'};
    printf("%c %d",k.a1,k.a2);
}