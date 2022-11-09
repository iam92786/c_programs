//Find max and min in a given array

#include<stdio.h>
#include<stdlib.h>

int main (void)
{
		//Takearray size from user
		int nth,i, *ptr, max, min;
		printf("Enter array size : ");
		scanf("%d",&nth);

		//creat array using calloc()
		ptr = (int*)calloc(nth,sizeof(int));
		if(ptr == NULL)
		{
				perror("ptr : calloc() failed !");
				exit(0);
		}

		//Take array element from user
		printf("Enter array element : ");
		for(i = 0; i < nth; ++i)
		{
				printf("arr[%d] = ",i);
				scanf("%d",(ptr+i));
		}

		//find max
		//find min
		max = ptr[0];
		min = ptr[0];
		for(i = 0; i < nth; ++i)
		{
				if(max < ptr[i])
				{
						max = *(ptr + i);
				}
				if(min > ptr[i])
				{
						min = *(ptr + i);
				}
		}
		printf("Max = %d, and Min = %d\n",max, min);
		
		free(ptr);
		return 0;
}

