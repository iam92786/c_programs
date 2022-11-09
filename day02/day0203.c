#include<stdio.h>

//AIM = Find minimum sum of factors of any given number.

int main (void)
{
		int num = 0;
		int div = 2;
		int sum = 0;

		//Take input from the user
		printf("Enter a number : ");
		scanf("%d",&num);
		printf("Minimum Sum of Factors of a given number %d is ",num);
		
        while(num > 1)
		{
			if (!(num % div))
			{
				num = num/div;

				sum = sum + div 	 		;
			}
			else
			{
				++div;
			}
		}
		//output print
		printf("%d\n",sum);
		return 0;
}
