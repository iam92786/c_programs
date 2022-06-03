#include<stdio.h>

//storage class = static
int main (void)
{
		static int num;
		scanf("%d",&num);
		printf("Static Storage Class Variable num = %d\n",num);


		return 0;
}
