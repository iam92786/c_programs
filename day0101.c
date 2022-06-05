#include<stdio.h>

//
//AIM : Try to demonstrate Globale Storage class in c language
//		String constant stored in rodata section

char *str = "Hello Innominds";
int main (void)
{
		printf("%s\n",str);
		return 0;
}
