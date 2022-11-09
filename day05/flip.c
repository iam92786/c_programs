//AIM : Flip bits of a given Number

#include<stdio.h>

int main (void)
{
		short int num;
		

		//Take input from the user
		printf("Enetr a  Number : ");
		scanf("%hd",&num);

		//Flip the given number
		num = num ^ 0xf;

		//Display the result
		printf("Output after flip bits is %hd\n",num); 

		return 0;
}
