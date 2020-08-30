#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, string argv[])
{
    
    //printf("%s\n", argv[1]);
    string key = argv[1];
    //printf("%s\n", key);
    
    
//if without key
    if (argc == 1) {
        printf("Usage: ./substitution key");
        return 1;
    }
//LENTH OF STRING  INPUT KEY   
    int len=strlen(key);

//LETTER TO INT TO CHECK IF ONLY LETTERS
    unsigned int array[len];//text string=>int array or one int ???
//ONLY LETTER ..............................................................^?
    for (int i=0; i < len; i++){
        array[i]=key[i];
        //printf("%i\n", array[i]);

        if ((array[i] >= 65 && array[i] <= 90) || (array[i] >= 97 && array[i] <= 122)) {
            continue;
        }
        else{
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    
//CHECK IF IS 26 LETTERS
    if (len!=26){
        printf("Key must contain 26 characters.");
        return 1;
    }

//IF LOWERCASE LETTER MAKE UPPERCASE------------

    char KEY[len];
    for (int k =0; k < len; k++){
        if (key[k] >='a'&& key[k] <='z'){
            KEY[k]= (char) (int) key[k] -32;
        }
        else{
        KEY[k]=key[k];
        }
    }
//MAKE LOWERCASE KEY ------------------------------------------
    char keys[len];
    for (int k =0; k < len; k++){
        if (key[k] >='A'&& key[k] <='Z'){
            keys[k]= (char) (int) key[k] +32;
        }
        else{
        keys[k]=key[k];
        }
    }

//ARRAY OF UPERCASE LETTERS
int Array[len];
    for(int s=0; s<len; s++){
        Array[s]=(int) KEY[s];

    }
    
//SORT ARRAY TO CHECK IF EVERY LETTER IS IN KEY
 int sortArray[len];   
    qsort (Array, len, sizeof(int), compare);
    for (int n=0; n<len; n++){
        sortArray[n]= Array[n];
        //printf(" %i ", sortArray[n]);
    }
//CHECK IF EVERY LETTER IS IN KEY (26)
    const int alfabet[26]={65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

    for (int l=0; l<26; l++){
        if (alfabet[l]!=sortArray[l]){
            printf("not all letters");
            return 1;
        }
    }


//plaintext:  ---------------------------------------------------------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");//INPUT TEXT
    char ciphertext[strlen(plaintext)]; //OUTPUT TEXT
    
    //const int alfabetAll[52]={65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    //    97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
   
    //array TEXT to NUMBER//////////////////////////
    unsigned int arrayPlaintext[strlen(plaintext)]; 
    for (int i=0; i < strlen(plaintext); i++){
        arrayPlaintext[i]=plaintext[i];
    }
    ////////////////////////////////////
    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("ciphertext: ");
    
    for (int z=0; z<strlen(plaintext); z++){ //for every letter in plaintext
        if (arrayPlaintext[z] >= 65 && arrayPlaintext[z] <= 90){ //DUŻE LITRY
            for (int b=65; b<=90; b++){
                if (arrayPlaintext[z]==b){
                    printf("%c", KEY[b-65]);
                    break;
                }
            } 
        }
        
    
        else if(arrayPlaintext[z] >= 97 && arrayPlaintext[z] <= 122) { //MAŁE LITERY
            for (int b=97; b<=122; b++){
                if (arrayPlaintext[z]==b){
                    printf("%c", keys[b-97]);
                    break;
                }
            }  
        }
        else printf("%c",plaintext[z]);
        
    }
    
    
    
    
    
    printf("\n");
    //return 0;
}