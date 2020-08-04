#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n=0;
    
    while (n<1||n>8)
    {
        n = get_int("Height: ");
    }
    char znaki[n-1];
    char odwrocone[n-1];
    for(int j=0; j<n; j++){
        znaki[j]=' ';
        odwrocone[j]=' ';
    }
    
    for(int i=0; i<n; i++){
        odwrocone[i]='#';
        znaki[n-1-i]='#';
        printf("%s  %s\n", znaki, odwrocone);
    }
   
}