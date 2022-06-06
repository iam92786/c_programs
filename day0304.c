#include<stdio.h>

//AIM : Find the GCD of Given 5 number

int main (void)
{
		int arr[5];
		int res, i, temp = 0;

		//take input from user
		printf("Enter The 5 numbers : ");

		for(i = 0; i < 5; ++i)
		{
				printf("%d = ",i);
				scanf("%d",&arr[i]);
		}

		//find the min
		temp = arr[0];
		for(i = 1; i < 5; ++i)
		{
				if(temp > arr[i])
				{
						temp = arr[i];
				}
		}

		//Find the GCD of Given 5 numbers
//		temp = arr[0];

		for(i = 0; i< (5-1); ++i)
		{
			while(temp != arr[i])
			{
				if(temp > arr[i])
				{
						temp = temp - arr[i];
				}
				else
				{
						arr[i] = arr[i] - temp;
				}
			}
		}
		printf("%d\n",temp);

    	return 0;
}
