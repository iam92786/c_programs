#include<stdio.h>

//AIM : Find the LCM of GIVEN TWO NUMBERS

int main (void)
{
		int num1, num2, res = 0;

		printf("Enter First number : ");
		scanf("%d",&num1);
		printf("Enter 2nd Number : "); 
		scanf("%d",&num2);

		printf("LCM (%d,%d) = ", num1, num2); 

		res = (num1 > num2) ? num1 : num2;
		while(1)
		{
				if((res % num1) == 0 && (res % num2) == 0)
				{
						printf("%d\n",res);
						break;
				}
				++res;
		}
		return 0;
}
