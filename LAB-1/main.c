#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*int i;
    printf("Odd Numbers from 200 to 250 are:\n");
    for(i=200;i<=250;i++)
    {
        if(i&1)
        {
           printf("Odd Number is:%d \n",i);
        }
    }*/

   /* int numbers[5];
    int i,largest;
    printf("Enter 5 integers:\n");
    for(i=0;i<5;i++){
        printf("Number %d:",i+1);
        scanf("%d",&numbers[i]);
        if(i==0 || numbers[i]>largest){
            largest=numbers[i];
        }
    }
    printf("\nThe largest number is: %d\n", largest);
    */
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    printf("\nBefore swapping: num1 = %d, num2 = %d\n", num1, num2);

    // Swap without temporary variable
    num1 = num1 + num2;
    num2 = num1 - num2;
    num1 = num1 - num2;

    printf("After swapping: num1 = %d, num2 = %d\n", num1, num2);

    return 0;
    return 0;

}
