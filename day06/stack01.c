#include<stdio.h>



long int stack(void)
{
		
		//register void* sp1 asm ("sp");
		int num = 100, num2 = 200;
		//char st = "a";
		register void* sp2 asm ("sp");
		//printf("Stack size = %p\n",sp2);
		return sp2;
}
int main (void)
{
		long int sp0;
		register void* sp1 asm ("sp");
		sp0 = stack();
		printf("SP : %p %p \n", sp1 , sp0);
		printf("Function stack size %d\n",(sp1-sp0));

		return 0;
}
