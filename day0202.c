#include<stdio.h>

//AIM : Find the GCD of the given Number.

int main (void)
{
		int num1, num2;

		//Take input from The User
		printf("Enter First number : ");
		scanf("%d",&num1);
		printf("Enter 2nd Number : "); 
		scanf("%d",&num2);

		printf("GCD (%d,%d) = ", num1, num2);

		//If negative number given by user, Than negative number change in to Positive number
		num1 = (num1 > 0) ? num1 : -num1;		//for First Number
		num2 = (num2 > 0) ? num2 : -num2; 		//for second Number

		//Find the GCD 
		while (num1 != num2)
		{
			if(num1 > num2)
			{
				num1 = num1 - num2;
			}
			else
			{
				num2 = num2 - num1;
			}
		}

		//Output, GCD of Two numbers Print.
		printf("%d\n",num1);

		return 0;
}
