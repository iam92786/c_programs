#include<stdio.h>

#define stack_size(end, start) (&start - &end)
int __attribute__((optimize("O0"))) add_fun(int a, int b)
{
    //---------------------------Auto var declaration Begin here
    char start;
    int ret = 10000, arr[100] = {11,22,33,44,55,66,77,88,99};
    char end;
    //---------------------------Auto var declaration end here
    ret = a + b;

    printf("addr of %p, %p\n",&start, &end);
    printf("%ld\n",stack_size(end, arr));

    return ret;
}

int main (void)
{

    printf("%d\n",add_fun(10,20));


    return 0;
}
