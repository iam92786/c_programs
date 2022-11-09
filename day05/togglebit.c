//AIM : Set Reset bits of a given integer (Particular position)

#include<stdio.h>
#define BV(n) (1<<(n))
int main (void)
{
		int num, pos;
		//take number from user
		printf("Enter a  number : ");
		scanf("%d",&num);

		//take position of particular bit which is going to be toggel
		printf("Enter the bit position : ");
		scanf("%d",&pos);

		//toggel the bit
		//num = num ^ (1 << (pos));
		num = num ^ BV(pos);

		//display output result
		printf("output : %d\n",num);


		return 0;
}
