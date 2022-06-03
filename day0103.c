#include<stdio.h>

//SSS = Storage Sign Size

int main (void)
{
	auto short int x ;
	scanf("%hd",&x);
	printf("x = %hd\n",x);

	return 0;

}
//Note : if the input is more than 2^(16) then out put is negative number 
//which is equal to the = 2^(16) - x
