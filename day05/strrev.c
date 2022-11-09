//AIM : Reverse given String.

#include<stdio.h>

int main (void)
{
		short int len = 0, i, size;
		char str[64];

		//take input from yhe user
		printf("Enter a string here : ");
		scanf("%[^\n]s",str);

		//calculate string length
		for(i = 0; str[i] ; ++i)
		{
				;
		}

		//reverse string
		printf("Reverse string :");
	
		--i;
		for(len = i; str[len] ; --len)
		{
				printf("%c",str[len]);
		}
		printf("\n");
		return 0;
}
