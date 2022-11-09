//Merge 2 given array using Pointer

#include<stdio.h>
#include<stdlib.h>

int main (void)
{
		//variable declaration
		int *ptr1, *ptr2,n1, n2;
		int i,j,size;
		
		//take data from the User
		printf("Enter the size of array - 1 : ");
		scanf("%d",&n1);

		printf("Enter the size o array - 2 : ");
		scanf("%d",&n2);

		//allocate the memory for the array
		ptr1 = (int*)calloc((n1+n2),sizeof(int));
		if (ptr1 == NULL)
		{
				perror("ptr1 : Calloc() failed !");
				exit(0);
		}
		ptr2 = (int*) calloc(n2, sizeof(int));
		if(ptr2 == NULL)
		{
				perror("ptr2 : Calloc() failed !");
				exit(0);
		}

		//take data from the user
		printf("Enter array 2 elements \n");
		for(i = 0; i < n2; ++i)
		{
				printf("arr2[%d] = ",i);
				scanf("%d",(ptr2+i));
		}

		printf("Enter araay 1 elements\n");
		for(i = 0; i < n1; ++i)
		{
				printf("arr1[%d] = ",i);
				scanf("%d",(ptr1+i));
		}

		//total size
		size = n1 + n2;

		//merge the 2 array
		for(i,j = 0; i < size; ++i,++j)
		{
				//printf("%d", i);
				*(ptr1 + i) = *(ptr2 + j);
		}

		//Display Merege Array elements
		printf("\n>>>Merge Array Elements<<<\n");
		for(i = 0; i < size; ++i)
		{
				printf("arr[%d] = %d\n",i,*(ptr1 + i));
		}

		//free the memory,which is  allocate by the  calloc()
		free(ptr1);
		free(ptr2);
		return 0;
}
