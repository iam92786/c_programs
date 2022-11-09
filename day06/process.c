#include<stdio.h>
#include<stdlib.h>


int main (int argc, char *argv[], char *evp[])
{
    int i;
    FILE *fp;
    //open file
    fp = fopen("file.txt","w+");
    if (fp == NULL)
    {
        printf("Error in file opening !\n");
        exit(1);
    }
    
    for(i = 0; evp[i]; ++i)
    {
        fprintf(fp,"%s\n",evp[i]);

    }

    for ( i = 0; i < argc; i++)
    {
        printf("%s\n",argv[i]);
    }
    
    fclose(fp);

    return 0;
}