#include<stdio.h>
#include<stdlib.h>

int main (void)
{
    char str;
    FILE *fp;
    short int count = 1;

    fp = fopen("mona_lisa.pgm","rb");
    if (fp == NULL)
    {
        perror("fopen() failed !!!");
        exit(1);
	}

    //read binary from the file
    for (int i = 0; count; i++)
    {
        count = fread(&str, sizeof(char),1,fp);
        if (count < 0)
        {
            printf("No record in the file");
            exit(1);
        }
        printf("%c ",str);
        
    }
    printf("\n");

    //closed the file
    fclose(fp);
    
    return 0;
}
