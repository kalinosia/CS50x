#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    //input only key ONE
    if (argc!=2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // input only numbers
    int argvInt[strlen(argv[1])];
    for (int i=0; i<strlen(argv[1]); i++){
        argvInt[i]=argv[1][i];
        if (!(argvInt[i] >= 48 && argvInt[i] <= 57)){
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //from string to int because input in string
    int key = atoi(argv[1]);
    //printf("%i\n", key);


    //scanf("%i", &key);
    //if (!(key>0 && key<1000)) return 1;
//ASK FOR INPUT KEY
    //string key = get_string("");
    //int key = get_int("");
    //if key!=int 
    //while (n < 1 || n > 8)
    //{
    //    n = get_int("Height: ");
    //}
    


//plaintext:  -------------------------------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");//IN
   //printf("%lu\n",strlen(plaintext));//indexs in IN
    int ciphertext[strlen(plaintext)]; //OUT
   // const int alfabetAll[52]={65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
   //     97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117};
    //array TEXT to NUMBER
    unsigned int arrayPlaintext[strlen(plaintext)];
    for (int i=0; i < strlen(plaintext); i++){
        arrayPlaintext[i]=plaintext[i];
    }
    ////////////////////////////////////
    
    printf("ciphertext: ");
    for(int p=0; p < strlen(plaintext); p++){ //for every letter in plaintext or number
        //printf("%i :", arrayPlaintext[p]);
        if (arrayPlaintext[p] >= 65 && arrayPlaintext[p] <= 90)  { //check if letter
            
            if (((arrayPlaintext[p]+key)%90)<65) ciphertext[p]=((arrayPlaintext[p]+key)%90)+64;
            else ciphertext[p]=((arrayPlaintext[p]+key)%90);
            
            printf("%c",ciphertext[p]);
        }
        else if (arrayPlaintext[p] >= 97 && arrayPlaintext[p] <= 122) {
            
            if (((arrayPlaintext[p]+key)%122) < 97) ciphertext[p]=((arrayPlaintext[p]+key)%122)+96;
            else ciphertext[p]=((arrayPlaintext[p]+key)%122);
            printf("%c",ciphertext[p]);
            
        }
        else{
                //ciphertext[p]=plaintext[p];//if not letter index 52 so not index in alfabet
                printf("%c",plaintext[p]);
            }
    }
    
    printf("\n");
    
    //return 0;
    
}