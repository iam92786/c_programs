//AIM : Legth of string
#include<stdio.h>

int main (void)
{
		unsigned short int len = 0,i;
		char str[32];

		//Take input from string
		printf("Enter a astring here : ");
		scanf("%[^\n]s",str);
		printf("%s\n",str);

		//calculate length of string
		for(i = 0; str[i]; ++i)
		{
				if(str[i] == ' ')
				{
						continue;
				}
			
				if(str[i] != '\0')
				{
						++len;
				}

		}
		printf("Length of string : %d\n",len);

		return 0;
}

