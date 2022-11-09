//Find Transpose of matrix(2D matrix).

#include<stdio.h>
#include<stdlib.h>

int main (void)
{
		//Take array size from user
		int row, col ,i,j, **ptr;
		int **mat;
		printf("Enter array size(row, column) : ");
		scanf("%d %d",&row, &col);

		//creat array(2D) using calloc()
		ptr = (int**)calloc(1,sizeof(int));
		if(ptr == NULL)
		{
				perror("ptr : calloc() failed !");
				exit(0);
		}
		for(i = 0; i < row; ++i)
		{
				ptr[i] =(int*)calloc(col, sizeof(int));
				if(ptr[i] == NULL)
				{
						perror("ptr[i] : calloc() failed !");
						exit(0);
				}
		}
		

		//Take array element from user
		printf("Enter array element : ");
		for(i = 0; i < row; ++i)
		{
				for(j = 0; j < col; ++j)
				{

						printf("ptr[%d][%d]  = ",i,j);
						scanf("%d",&ptr[i][j]);
				}
		}

		//Print Array before transpose
		for(i = 0; i < row ; ++i)
		{
				for(j = 0; j < col; ++j)
				{
						printf("%d\t",ptr[i][j]);
				}
				printf("\n\n");
		}
		printf("\n");

		//Display after Transpose
		for ( i = 0; i < col; i++)
		{
			for ( j = 0; j < row; j++)
				{
						printf("%d\t",ptr[j][i]);
				}
				printf("\n\n");
		}
		printf("\n");

		for(i = 0; i < row; ++i)
		{
				free(*(ptr + i));
		}		
		free(ptr);

		return 0;
}
