//Sorting Algorithem : Bubble Sort

#include<stdio.h>


int main (void)
{
		int arr[5];
		int temp,i,j;
		int n = (sizeof(arr)/sizeof(arr[0]));

		//1 Take input from User
		printf("Enter the Array element : \n");
		for(i = 0; i < n; ++i)
		{
				printf("arr[%d] = ",i);
				scanf("%d",&arr[i]);
		}

		//2 Apply sorting algo
		for(i = 0; i < n; ++i)
		{
				for(j = 0; j < n-1; ++j)
				{
						//3 swap the elelment of the array
						if(arr[j] > arr[j+1])
						{
								temp = arr[j];
								arr[j] = arr[j+1];
								arr[j+1] = temp;
						}
				}
		}

		//4 Display sorted array
		printf("arr[%d] = { ",n);
	
		for(i = 0; i < n; ++i)
		{
				printf("%d ",arr[i]);
		}
	
		printf("}");

		return 0;
}


