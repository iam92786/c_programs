//Write a function to find Big endianness and littel endiannes

#include<stdio.h>


int main (void)
{
		int num = 0x45;//0x41 stored in 4 byte of memory

		char *ptr;
		ptr =(char*) &num;	//base address of 'num' variable store in 'ptr' pointer

		if(*ptr == 0x45)
		{
				printf("Littel Endian\n");
		}
		else
		{
				printf("Big Endian\n");
		}
		return 0;
}
