#include<stdio.h>
#include<stdlib.h>

//AIM : Find whether the given number is Prime number or Not.

int main (void)
{
		int num = 0, i = 0;
		printf("Enter a number :");
		scanf("%d",&num);
		printf("%d",num);

		if(num == 1 || num == 2)
		{
				printf(" : Prime Number\n");
				exit(0);
		}

		for(i = 2 ; i <= (num/2) ; ++i)
		{
			if((num % i) == 0)
			{
					printf(" : Not Prime Number\n");
					exit(0);
			}
		}
		printf(" : Prime Number\n");
		return 0;
}
