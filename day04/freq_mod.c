//Highest Frequency of a charachter in a given string.

#include<stdio.h>

typedef struct node{
		int ind_no;
		char ch;
		int count;
}node_t;
#define LENGTH 32

int main (void)
{
		node_t ind[LENGTH];
		char str[LENGTH];
		int i, j, sno = 0,size;

		//1 Take string from user
		printf("Enter String here :");
		scanf("%[^\n]s",str);
		printf("%s\n",str); //display

		//2 make entry in structure
		for(i = 0; str[i]; ++i)
		{
				if(i == 0) //first entery
				{
						ind[i].ind_no = i;
						ind[i].count = 0;
						ind[i].ch = str[i];
						continue;
				}

				if(str[i] == ' ')//come outof current iterarion, if it is space in string
				{
						continue;
				}
				
				// check Repeatation of char in string
				for ( j = 0; j < str[j]; j++)
				{
					if (str[].ch == ind[j].ch)
					{
						ind[i].count++;
						continue;
					}
					else
					{
						ind[i].ch = str[i]
					}
					
					
				}
				
				/*
				count = 0;
				for(j = 0; str[j] ; ++j)
				{
						if(str[i] == str[j])
						{
								++count;
						}
				}
				printf("%c = %d\n",str[i], count);
				*/
		}

		
		//3 display

		return 0;
}
