#include<stdio.h>
//AIM : Find the Length of string(Only number of character in a string).

int main (void)
{
    char str[32];
    int count = 0;
    printf("Enter a string here : ");
    scanf("%[^\n]s",str);   //Take string from user until newline = \n 

    for (int i = 0; str[i]; i++) //until null not come into string
    {
        if(str[i] != 32)   //condition check for Space in the given string
        {
            ++count;
        }
    }

	//output result print
    printf("%d\n",count);

    return 0;
}
