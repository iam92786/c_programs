//Highest Frequency of a charachter in a given string.

#include<stdio.h>

#define LENGTH 32

int main (void)
{
		char str[LENGTH];
		int i, j, count = 0,sno;

		//1 Take string from user
		printf("Enter String here :");
		scanf("%[^\n]s",str);
		printf("%s\n",str); //display

		//2 make entry in structure
		for(i = 0; str[i]; ++i)
		{

				if(str[i] == ' ')//come outof current iterarion, if it is space in string
				{
						continue;
				}
				
				count = 0;
				for(j = 0; str[j] ; ++j)
				{
						if(str[i] == str[j])
						{
								++count;
						}
				}

			here:	printf("%c = %d\n",str[i], count);

		}

		
		//3 display

		return 0;
}
