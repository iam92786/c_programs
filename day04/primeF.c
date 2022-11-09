//AIM :Find the Prime Factor of the given number

#include<stdio.h>

#define true 1
#define false 0

int main (void)
{
		//1. Take number from the user in 'num' variable.
		int num, i, primenum, j,temp;

		printf("Enter a number here :");
		scanf("%d",&num);
		printf("All the Prime Factor %d is = ",num);
		

		temp = num/2;
		//4. Then find all factors.
		
		for(i = 2; i <= num/2; ++i)
		{

				//check i is factor of given num
				if((num % i) == 0)
				{
						primenum = true;
						//printf("Factor %d\n",i);
						//check is it prime
						for(j = 2; j <= i/2; ++j)
						{
								if(i % j == 0)
								{
										primenum = false;
										break;
								}
						}
						if(primenum == 1)
						{
								printf("%d ,",i);
						}
				}
		}

		return 0;
}
