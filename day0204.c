#include<stdio.h>

//Reset(0) Most Right side Active high(1) Bit in the given number

int main (void)
{
		int num, temp;

		//Take input from user
		printf("Enter a Number : ");
		scanf("%d",&num);
		
	
		temp = num - 1;
		num = num & temp;
		
		//Print Output result
		printf("output is = %d\n",num);

		return 0;
}

