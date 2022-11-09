//Read PGM image and Draw a  histogram

#include<stdio.h>
#include<stdlib.h>

argv[1] = file name with path

argv[2] == rb

int main (int argc, char *argv[])
{
    FILE *fp;
    int count = 1;
    char str;

    fp = fopen(argv[1],argv[2]);
    if (fp == NULL )
    {
        perror("fopen () Failed !!!");
        exit(1);
    }
    
    for (int i = 0; i < 100; i++)
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

    fclose(fp);
    return 0;
}
