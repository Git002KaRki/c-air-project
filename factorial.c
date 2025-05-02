#include <stdio.h>
    int main()
     {
        int num;
        int fact=1;
        printf("Enter a number:");
        scanf("%d",&num);
        for(int i=2;i<=num;i++)
        {
            fact=fact*i;
        }
        printf("factorial is %d",fact);
        return 0;
    }
    

