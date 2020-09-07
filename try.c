#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <stdlib.h> //malloc
#include <string.h>

#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

#define LENGTH 45


typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26*26; //later maby  24*24

// Hash table
node *table[N];
                                    //Hashtable malloc etc WALKTHROUGHTS
                                    // node *n = malloc(sizeof(node));
                                    // strcpy(n->word, "Hello"); //stingcopy copy string from source to destination
                                    // n->next=NULL;
int main(void)
{
    printf("STRAT\n");


    FILE *dic = fopen(DICTIONARY, "r");
    if (dic == NULL) return 1;

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //int x=hash("COŚ");
    //hashtable[x]="COŚ"

    //bool new_word=false; //every first letter in new word you must check if change a, b, c, ... z
    ///////int x=0; //x max is 24 because a, c, b, d, ... z = 26
    //for (int d = fgetc(dic); d != EOF; d = fgetc(dic)) //fget() get the next u. char; EOF end of file; get next
    //for (int d = fscanf(dic); d != EOF; d = fscanf(dic))
    int x=0;
    char scawor[LENGTH];
    //printf("before looop\n");
    while (fscanf(dic,"%s", scawor) != EOF)
    {
        //printf("loop\n");
        //fscanf(dic, "%c", scawor); //znajdź string
        /*if (EOF){
           printf("break\n");
           break; //??? if return EOF
           printf("break\n");
        }
        */
        /*
        unsigned int create(char* a)
{   int x = create("John");

    int n = hash(a);
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) exit(1);
    else
    {
        new_node->name = a;
        new_node->next = hashtable[n];
        hashtable[n] = new_node;
    }
    return n;
*/
        //printf("%s\n", scawor);
        int a = hash(scawor);
        //printf("HASh: %i\n", a);
        //printf("%s\n", scawor);////////////////////////////////////////////////
        node *n=malloc(sizeof(node)); //przygotuj miejsce
        if (n == NULL) return 1;
        strcpy(n->word, scawor);
        n->next=table[a];
        table[a]=n;
        //printf("%s\n", n->word);




        /*
        strcpy(n->word, scawor); //kopij słowo
        n->next=NULL;

        printf("%s\n", n->word);

        int hashValue=hash(n->word);/////////////////////////
        printf("Hash value: %i\n", hashValue);

        if(table[hashValue] != NULL){
            n =table[hashValue]->next;
            table[hashValue]=n;
        }else{
            table[hashValue]=n;
        }


         */

       //table[x].word[lenght+1]
        //table[x].next //POITER TO NEXT

       /*
        n->word = word??;
        n->next = NULL;
        table[s]=n; //pierwszy
        table[s]->next = n; //reszta
        */
        //fscanf(dic, "%c", word);
       // printf("%s", n->word);
        //printf("END");
        /*
        if ( new_word == true)
        {
            if ( d != first_letter) x++; //if a change to b, b to c, c to d,... x max =24 -> table[x]
            //table[x]->next =  //POITER TO NEXT?????????????????????????????
            new_word=false;
        }

        table[x]->word[index] = d;
        index++;

        if (table[x]->word[index] == '\n') //ale chyba d=
        {
            index=0;
            new_word=true;
        }

        printf("%c", d);

         //IF U WANT ERRORS IF YOUR DICTIONARY MAY NOT GOOD HERE IS SPACE?
        //FOR EXAPLE NUMBERS,  LENGHT,
        */
    }
    //printf("END\n");

    for (int i=0; i<N; i++){
        if (table[i]!=NULL) printf("%i: %s\n", i,table[i]->word);
    }
    /////////////////////////////////////////
    struct node *step;
    step=table[182];
    //string current=table[182]->next;
    step=step->next;
    printf("%s\n", step->word);
    step=step->next;
    printf("%s\n", step->word);
    //////////////////////////////////

}
// Hashes word to a number
unsigned int hash(const char *word)
{
    //struct one
    // TODO
    //printf("%s\n", word);
    //string slowo=*word;
    //printf("%s\n", slowo);
    //int first=(int) malloc(sizeof(int));
    int first;
    int second;
    //int third;

    //printf("word 0: %c, %i \n", word[0], word[0]);
    for (int j=0; j<2; j++){
        for (int i=0; i<=26; i++){
            if ((int) word[j] == 65+i || (int) word[j] == 97+i){
                if (j==0) first=i;
                if (j==1) second=i;
                //if (j==2) third=i;
            }
        }

    }
    //first*26*26+second*26+third
    return first*26+second;
    //free(first);
}









/* 
//open dictionariy file
     FILE *dic = fopen(dictionary, "r"); 
     if (dic == NULL) return false;
    
    //read strings from file
    //fscanf(file, "%s", word);
    //if end of file terurn EOF
    
    //int x=hash("COŚ");
    //hashtable[x]="COŚ"
    
    char first_letter = fgetc(dic); //first letter first word is probably a but if small dictionaty check
    int index=0; //index in string word
    bool new_word=false; //every first letter in new word you must check if change a, b, c, ... z
    int x=0; //x max is 24 because a, c, b, d, ... z = 24
    
    for (int d = fgetc(dic); d != EOF; d = fgetc(dic)) //fget() get the next u. char; EOF end of file; get next
    {
        //table[x].word[lenght+1]
        //table[x].next //POITER TO NEXT
        node *n=malloc(sizeof(node));
        if (n == NULL) return 1;
        n->word = word??;
        n->next = NULL;
        table[s]=n; //pierwszy
        table[s]->next = n; //reszta
        
        if ( new_word == true)
        {
            if ( d != first_letter) x++; //if a change to b, b to c, c to d,... x max =24 -> table[x]
            table[x].next =  //POITER TO NEXT?????????????????????????????
            new_word=false;
        }
        
        table[x].word[index] = d;
        index++;
        
        if (table[x].word[index] == '\n') //ale chyba d= 
        {
            index=0; 
            new_word=true;
        }
         //IF U WANT ERRORS IF YOUR DICTIONARY MAY NOT GOOD HERE IS SPACE?
        //FOR EXAPLE NUMBERS,  LENGHT, 
    }
    */