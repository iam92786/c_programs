//AIM : Find out maximum freq cahrachter in a string

#include<stdio.h>
#include<string.h>

int main (void)
{
		//take input from user
		short int i,j, max_count = 0, count;
		char str[32], max_char;

		printf("Enter the String : ");
		scanf("%[^\n]s",str);
		
		//find the freq of charachter
		for(i = 0; i < str[i]; ++i)
		{
				if(str[i] == ' ')
				{
						continue;
				}
				count = 0;
				for(j = 0; str[j]; ++j)
				{
						if(str[i] == str[j])
						{
								++count;
						}
				}
				if(count > max_count)
				{
						max_count = count;
						max_char = str[i];
				}
		}
		//find the ma freq
		printf("maximum freq char is %c, freq = %d\n",max_char,max_count);

		return 0;
}
