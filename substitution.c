#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(void)
{
    //string key = get_string("");
    //int x= strlen(key);
    //printf("%i",x);

//ASK FOR INPUT KEY
    string key = get_string("");

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
            printf("Muszą być litery...........\n");
            return 0;
        }
    }
//CHECK IF IS 26 LETTERS
    if (len!=26){
        printf("Key must contain 26 characters.");
        return 0; //????????
    }
    
//IF LOWERCASE LETTER MAKE UPPERCASE 
    char KEY[len];
    for (int k =0; k < len; k++){
        if (key[k] >='a'&& key[k] <='z'){
            KEY[k]= (char) (int) key[k] -32;
        }
        else{
        KEY[k]=key[k];
        }
    }


//SORT ARRAY TO CHECK IF EVERY LETTER IS IN KEY
    int sortArray[len];
    qsort (array, len, sizeof(int), compare);
    for (int n=0; n<len; n++){
        sortArray[n]= array[n];
        //printf(" %i ", sortArray[n]);
    }
//CHECK IF EVERY LETTER IS IN KEY (26)
    const int alfabet[26]={65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
    for (int l=0; l<26; l++){
        if (alfabet[l]!=sortArray[l]){
            printf("not all letters");
        }
    }
    
//plaintext:  -------------------------------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");
    int index[strlen(plaintext)];
    int ciphertext[strlen(plaintext)];
    
    //array
    for(int p=0; p<strlen(plaintext); p++){ //for every letter in plintext
        for (int f=0; f<26; f++){           //looking for in alfabet
            if (plaintext[p]==alfabet[f]){  //if first letter in plaintext == letter in alfabet
                index[p]=f;              // want indext this letter in alfabet
            }
        }
    }
    for (int z=0; z<strlen(plaintext); z++){ //for every letter in plaintext
        ciphertext[z]=key[index[z]];        //letter in ciphertext = get index from alfabet and give it to key[index]
    }
    printf("ciphertext: ");
    for (int x=0; x<strlen(plaintext); x++){ // for every letter in ciphertext (int!!)
        printf("%c", ciphertext[x]);        //print char not int
    }
}