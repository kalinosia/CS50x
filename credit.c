#include <stdio.h>
#include <cs50.h>

int main(void)
{
    unsigned long long numer = get_long("Number: ");
    //printf("%llu\n",numer);
    unsigned  long ten=10000000000; //ten zero
    ////////////////////////////
    unsigned long long num=numer;
    int a=0;
    int suma=0;
    int b=0;
    int c=0;
    int sumb=0;
    int sum=0;
   //////////////////////////////////////////
   for(int i=1;i<=8;i++){
   a=num % 10;
   suma=suma+a;
   num=num-a;
   num=num/10;
   
   c=num % 10;
   b=c*2;
   sumb=sumb+b;
   num=num-c;
   num=num/10;
   }
   
   sum=suma+sumb;
   if(sum%10!=0){
       printf("INVALID\n");
       return 0;
   }
   //////////////////////////////////////////////
    
    if (numer<999999999999){
        printf("INVALID\n");
    }
    //else if ((numer>=(100*ten)&&numer<(1000*ten))||(numer>=(10000*ten)&&numer<(100000*ten))){//Visa uses 13- and 16-digit numbers
    else if ((numer>=(400*ten)&&numer<(500*ten))||(numer>=(400000*ten)&&numer<(500000*ten))){//and all Visa numbers start with 4
        printf("VISA\n");
    }                                                                                                   //MasterCard uses 16-digit numbers
    else if(numer>=(510000*ten)&&numer<(560000*ten)){      //most MasterCard numbers start with 51, 52, 53, 54, or 55
            printf("MASTERCARD\n");                             
    }
    else if (numer>=(10000*ten)&&numer<(10000*ten)){//American Express uses 15-digit numbers,
        printf("American Express???\n");
    }
    else if ((numer>=(340000000000000)&&numer<(350000000000000))||(numer>=(370000000000000)&&numer<(380000000000000))){//All American Express numbers start with 34 or 37;
        printf("AMEX\n");
    }
    else{
        printf("INVALID\n");
    }
}