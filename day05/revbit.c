//Reverse  bits of the given integer

#include<stdio.h>

int main (void)
{

		char num = 0, temp, out = 0;
		printf("Enter a number : ");
		scanf("%d",&num);
		
		
		//Rev bits
		for(int i = 0; i < 8; ++i)
		{
				//fetch each bit at unit place
				temp = (num >> i) & 0x01 ;

				//left shift and Add all bit
				out = out | (temp << (7 - i));

		}
		printf("Rev of %d is %d\n",num, out);

		return 0;
}
