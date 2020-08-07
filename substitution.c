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
    

    //string key = get_string("");
//if without key
    if (argc == 1) {
        printf("Usage: ./substitution key");
        return 1;
    }
//ASK FOR INPUT KEY    
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

//IF LOWERCASE LETTER MAKE UPPERCASE
/* NOT
    char KEY[len];
    for (int k =0; k < len; k++){
        if (key[k] >='a'&& key[k] <='z'){
            KEY[k]= (char) (int) key[k] -32;
        }
        else{
        KEY[k]=key[k];
        }
    }
*/
//EVERY LETTER UPPERCASE

int Array[len];
    for(int s=0; s<len; s++){
        if (array[s]>=97 && array[s]<=122){
            Array[s]=array[s]-32;
        }
        else{
            Array[s]=array[s];
        }

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

//plaintext:  -------------------------------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");//IN
    int index[strlen(plaintext)];//indexs in IN
    int ciphertext[strlen(plaintext)]; //OUT
    const int alfabetAll[52]={65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
        97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    //array TEXT to NUMBER
    unsigned int arrayPlaintext[strlen(plaintext)];
    for (int i=0; i < strlen(plaintext); i++){
        arrayPlaintext[i]=plaintext[i];
    }
    ////////////////////////////////////
    
    
    for(int p=0; p<strlen(plaintext); p++){ //for every letter in plaintext or number
        if ((arrayPlaintext[p] >= 65 && arrayPlaintext[p] <= 90) || (arrayPlaintext[p] >= 97 && arrayPlaintext[p] <= 122)) { //check if letter
            for (int f=0; f<52; f++){           //looking for in alfabet
                if (plaintext[p]==alfabetAll[f]){  //if first letter in plaintext == letter in alfabet
                    index[p]=f;              // want indext this letter in alfabet
                }
            }
        }
        else{
                index[p]=-1;//if not letter index 52 so not index in alfabet
            }
    }
    
    printf("ciphertext: ");
    for (int z=0; z<strlen(plaintext); z++){ //for every letter in plaintext
        if (index[z]==-1) {
            //printf("LICZBA\n");
            //ciphertext[z]=plaintext[z];
            printf("%c",plaintext[z]);
        }
        else {
            if (index[z]>=26){
                index[z]=index[z]-26;
                char bigLetter =key[index[z]];
                printf("%c", bigLetter);/////////////////
                //ciphertext[z]=((int) ciphertext[z]+32);
                
                printf("%d", ciphertext[z]);
            }
            else{
            ciphertext[z]=key[index[z]]; //letter in ciphertext = get index from alfabet and give it to key[index]
            }
            printf("%c", ciphertext[z]); 
    }}
    
    //for (int x=0; x<strlen(plaintext); x++){ // for every letter in ciphertext (int!!)
      //  if (index[p]==x) printf("%i",ciphertext[x]);
        //else printf("%c", ciphertext[x]);        //print char not int
    //}
    printf("\n");
    //return 0;
}