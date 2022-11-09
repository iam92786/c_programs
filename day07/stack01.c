#include<stdio.h>

// calculate size of stack

int function1()
//int function1(int a, int b,int e, int c, int d)
{
		register char *const sp asm("esp");
		int size_stack = 100;
		int arr[2] = {1,0}, arr1 = 20;
		//size_stack = sizeof(int) + sizeof(d) +  (char *)&a - (char *)&d;
		//int arr[100];		

		printf("bp - sp = ");

		register char *const bp asm("ebp");
		return (bp - sp);
}

int main (void)
{
		int stack;
		//stack = function1(10,20,30,40,50);
		stack = function1();
		printf("size of stack  = %d\n",stack);
		return 0;
}
