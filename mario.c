#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int n=0;
    
    while (n<1||n>8)
    {
        n = get_int("Height: ");
    }
    /*
    int q=n-1;
    char znaki[n];
    char odwrocone[n];
    printf("TU: %s  %s\n\n", znaki, odwrocone);
    for(int j=0; j<n; j++){
        znaki[j]='_';
        odwrocone[j]='_';
    }
    */
    int h=2*n+2;
    char linia[h];
    for(int j=0; j<h; j++){
        linia[j]=' ';
    }
    linia[h]='\0';
    int z=1;
    for(int i=0; i<n; i++){
        linia[n-z]='#';
        linia[n+z+1]='#';
        printf("%s\n", linia);
        z++;
    }
    
   
}