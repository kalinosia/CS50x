// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h>

#include "dictionary.h"
unsigned int hash(const char *word);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26*26; //later maby  26^3

// Hash table
node *table[N];

//Hashtable malloc etc WALKTHROUGHTS
// node *n = malloc(sizeof(node));
// strcpy(n->word, "Hello"); //stingcopy copy string from source to destination 
// n->next=NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    
    //we need this?? probably not
    char *name = malloc(sizeof(char[strlen(word)])); //len(word) = [LENGTH + 1] ? 
    strcpy(name, word);
    //printf("%s\n", name);
    //printf("%s\n", word);
    for (int a = 0; a < strlen(word); a++){ 
        if (word[a]>=95 && (int) word[a]<=90){
            name[a]=word[a]+26;
        }
    }
    
    int address=0;
    for (int i=0; i<=26; i++){
        if ((int) word[0] == 65+i || (int) word[0] == 97+i){
            for (int j=0; j<=26; j++){
                if ((int) word[1] == 65+j || (int) word[1] == 97+j){
                    address = i * 26 + j;
                }
            }
        }
    }
    
    node *prt=table[address];
    while(prt!=NULL)
    {
        if (strcmp(prt->word,name)==0){
            free(name);
            return false;
        }
        prt=prt->next;
    }
    free(name);
    return true;
    
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int first;
    int second;
    

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
    

}

int words=0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
     FILE *dic = fopen(dictionary, "r");
    if (dic == NULL) return false;

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    char scawor[LENGTH];

    while (fscanf(dic,"%s", scawor) != EOF)
    {
        int a = hash(scawor);
        node *n=malloc(sizeof(node)); //przygotuj miejsce
        if (n == NULL) return false;
        strcpy(n->word, scawor);
        n->next=table[a];
        table[a]=n;
        words++;
    }
    return true;
        
            
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    
    //printf("Words: %i \n", words);
    
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    struct node *step;
    // TODO
    
    for (int i=0; i<N; i++){
        step=table[i];
        
        if (step==NULL) continue;
        else if (table[i]->next==NULL) free(step);
        else
        {
            while(table[i]->next==NULL){
                step=step->next;
                //printf("%i: %s\n", i,step->word);
                    if (step->next==NULL) {
                        free(step);
                        step=table[i];
                    }
                    
            }
            free(step);
        }
    }
    return true;
    
    /////////////////////////////////////////
    /* HOW IT WORKS FOR EXAMPLE
    step=table[182];
    printf("%s\n", table[182]->word); //hazy - 55689 in large
    step=step->next;
    printf("%s\n", step->word); //hazlitt
    step=step->next;
    printf("%s\n", step->word); //hazing
    */
    
    
    
    return false;
}

/*
///////////////////////////////////
if (X >= 65 && X <= 90){
    //for (int i=65; i <= 90; i++){
    X=X+32;
}
read dictionary

fread(dic_word, sizeof(c)*LENGHT, 143091, file?); //if char dic_word (not *)// then here &dic_word
//free(dic_word); //end of my program

SORT IN HASH TABLE??
    y = hash("dicWord[x]");
    hashtable[y]="dicWord[x]";
    

LOOKING FOR IN DICTIONARY        
    for (int i = 0; i < 25; i++){
        if (word[0] == 65+i || word[0] == 97+i)
        {
            go to hash table[i] (np. a = 0 z = 24) Słownik
            for (int i = 0; i < 25; i++){
                if (word[1] == 65+i || word[0] == 97+i)
                {
                    go to hash table[i] (np. a = 0 z = 24) Słownik
                    
                }
    }
        }
    }
    */
