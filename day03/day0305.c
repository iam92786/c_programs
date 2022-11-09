
//AIM : Find the LCM of Given nth numbers

#include<stdio.h>

int main (void)
{
    int arr[5];
    int i = 0, temp = 0, count;
    int res;

    //take total number of element from the user
    printf("Enter the total number of element : ");
    scanf("%d",&count);

    //take element of array from User
    printf("Enter The Number : ");
    for ( i = 0; i < count; ++i)
    {
        printf("%d = ",i);
        scanf("%d",&arr[i]);
    }
    

    //find the LCM of two number from array
    temp = arr[0];
    for (i = 1; i < (count-1); ++i)
    {
        //printf("%d\n",arr[j]);
        res = (temp > arr[i]) ? temp : arr[i]; //initialized 'res' variable with bigger value between 'temp' and 'arr' variable
        while (1)
        {
            if((res % temp) == 0 && (res % arr[i]) == 0)
            {
                temp = res;
                //printf("%d\n",res);
                break;
            }
            ++res;
        }

    }
    printf("LCM = %d\n",res);
    return 0;
}

//NOTE : n should be 3 or more than numbers 
