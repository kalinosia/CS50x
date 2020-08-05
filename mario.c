#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int n=0;
    
    while (n<1||n>8)
    {
        n = get_int("Height: ");
    }
    int z=1;
     for (int i = 0; i < n; i++){
        for(int k=0; k<n-z; k++){
            printf(" ");
         }
        for (int j = 0; j < z; j++){
          printf("#");
        }
        printf("\n");
        z++;
        }
    
   
}