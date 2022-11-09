
#include<stdio.h>

#define arr_size(arr) (char*)(&arr+1) - (char*)(&arr)
int main (void)
{
		int arr[100] = {11,22,33,44,55};
		int i;

		//Find out memory allocated for array using macros  
		printf("arr_size(arr) =  %ld\n",arr_size(arr));

		for(i = 0; arr[i]; ++i)
		{
			printf("arr[%d]\n",i);
		}
		printf("%d\n",(i * 4));
		

		return 0;
}
