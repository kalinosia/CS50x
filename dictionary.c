// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> //strcpy
#include <strings.h> //!!!!! strcasecmp not in string!!!

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
    // to strcmp is good but i have strcasesmp
    //we need this?? probably not
    char name[strlen(word)]; //= malloc(sizeof(char[strlen(word)])); //len(word) = [LENGTH + 1] ? gwiazdka prze name 
    //if (name == NULL) return -1; //??
    //strcpy(name, word);
    
    for (int a = 0; a < strlen(word); a++){ 
        if ((int) word[a] >= 65 && (int) word[a] <= 90){
             name[a] =  word[a] +32;
        }else{
            name[a]=word[a];
        }
        
    }
    //*/
    //printf("Word: %s; name: %s.\n", word, name);
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
    //int h=hash(word);
    node *prt=table[address];
    //bool yes=false;
    if (prt==NULL) return false;
    while(prt!=NULL)
    {
        //if (strcmp(prt->word,name)==0){ //To compare two strings case-insensitively, you may find #strcasecmp# (declared in strings.h) useful!
        //if (strcasecmp(prt->word,word)){ 
        if (strcmp(prt->word,name)){     
            //free(name);
            //yes=true;
            return true;
        }
        else prt=prt->next;
    }
    //if (yes==false) free(name);
        return false;

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
            //find where in table if a, d or t ...
        int a = hash(scawor);
            // Mallocs a node for each new word
        node *n=malloc(sizeof(node)); //przygotuj miejsce
        if (n == NULL) return false;
            //Copies word into node if malloc succeeds
        strcpy(n->word, scawor);
        
        // Initializes head to point to hashtable index/bucket
        node *head = table[a];

        // Inserts new nodes at beginning of lists
        if (head == NULL)
        {
            table[a] = n;
            words++;
        }
        else
        {
            n->next = table[a];
            table[a] = n;
            words++;
        }
    }
    //fclose(file);
    
    /*seams to work but probably something not enought...
        n->next=table[a];
        table[a]=n;
        words++;
    }
    */
    /*
    struct node *step;
    step=table[185]; // 182
    printf("%s\n", table[185]->word); //hazy - 55689 in large 
    step=step->next;
    printf("%s\n", step->word); //hazlitt
    //step=step->next;
    //printf("%s\n", step->word); //hazing
    */
    //printf("%s\n", table[182]->next->word);
    /*
    for (int k=0; k<N; k++){
        printf("%s  ", table[k]->word);
    }
    */
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
    int how_many=0;
    
    node *head = NULL;
    node *cursor = head;
    // freeing linked lists
    for (int i=0; i<N; i++){
        cursor=table[i];
        //printf("%s  ", cursor->word);
        if (cursor==NULL) continue;
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            how_many++;
        }
    }
    
    //printf("UNLOADED: %i\n", how_many);
    if (words == how_many) return true;

    else return false;
    
}

    
    /*
    struct node *step;
    //step=(node *)malloc(sizeof(node));
    int how_many=0;
    
    for (int i=0; i<N; i++){
        step=table[i];
        
        //free(step);
        //how_many++;
        
        //if (step==NULL) continue;//??
        while(1){
            if (table[i] == NULL) break;
            if (step->next == NULL && step != NULL)
            {
                //printf("string: %s", step->word);
                free(step);
                how_many++;
                step=table[i];
                continue;
            }
            while(step->next != NULL){
                step=step->next;     
            }
            
            
        }*/
           /* else if (step->next==NULL){
                    free(step);
                    printf("Go");
                    how_many++;
                    step=table[i];
            }
            
            else 
        }
        */
    //}
        //double free or corruption (fasttop) Aborted */
//////////////////////////////////////////////////////////////////////
    /* WORK BUT NOT ENOUGH
    for (int i=0; i<N; i++){
        step=table[i];
        
        if (step==NULL) continue;
        else if (table[i]->next==NULL) {
            how_many++;
            free(step);
        }
        else
        {
            while(table[i]->next==NULL){
                step=step->next;
                //printf("%i: %s\n", i,step->word);
                    if (step->next==NULL) {
                        free(step);
                        how_many++;
                        step=table[i];
                    }
                    
            }
            free(step);
            how_many++;
        }
    }
    
    printf("UNLOADED: %i\n", how_many);
    if (how_many==words) return true;
    else return false;
    
    //UNLOADED: 470 Could not unload dictionaries/large. */
    
    
    
    
    
    
    /////////////////////////////////////////
    /* HOW IT WORKS FOR EXAMPLE
    step=table[182];
    printf("%s\n", table[182]->word); //hazy - 55689 in large
    step=step->next;
    printf("%s\n", step->word); //hazlitt
    step=step->next;
    printf("%s\n", step->word); //hazing
    //*/
    
    
    

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
