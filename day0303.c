#include<stdio.h>

//AIM : Find the LCM of Given 5 number

int main (void)
{
    int arr[5];
    int i = 0, temp = 0;
    int res;
    
	//recive 5 element of array from User
    printf("Enter The Number : ");
    for ( i = 0; i < 5; ++i)
    {
        printf("%d = ",i);
        scanf("%d",&arr[i]);
    }
    
    //find the LCM of two number from array
    temp = arr[0];
    for (i = 1; i < 5; ++i)
    {
       
        res = (temp > arr[i]) ? temp : arr[i];
        while (1)
        {
            if((res % temp) == 0 && (res % arr[i]) == 0)
            {
                temp = res;
                break;
            }
            ++res;
        }

    }
	//output
    printf("LCM(%d, %d, %d, %d, %d) = %d\n",arr[0], arr[1], arr[2], arr[3], arr[4],res);
    return 0;
}
