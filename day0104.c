#include<stdio.h>

//AIM : Try to demonstrate storage class = static

int main (void)
{
		static int num;
		printf("Enter a Number : ");
		scanf("%d",&num);
		printf("Static Storage Class Variable num = %d\n",num);
		return 0;
}
