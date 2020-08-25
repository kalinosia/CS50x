#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include <math.h>


int main(void)
{
    string text = get_string("Text: ");
    
    unsigned int letters=0;
    unsigned int words=0;
    unsigned int sentences=0;
    
    unsigned int array[strlen(text)];//text string=>int array or one int ???
    
    for (int i=0; i <= strlen(text); i++){
        array[i]=text[i];
        //printf("%i\n", array[i]);
        
        if ((array[i] >= 65 && array[i] <= 90) || (array[i] >= 97 && array[i] <= 122)) {
            letters++;
        }
        else if (array[i] == 32 || array[i] == 0){//space what abaut different
            words++; 
        }
        else if(array[i] == 46 || array[i] == 63 || array[i] == 33){//. ? !
            sentences++;

        }
    }
    //printf("Words: %i\n", words);
    //printf("Letters: %i\n", letters);
    //printf("Sentence: %i\n", sentences);
    
    //words++;//BECAUSE LAST WORD!!
    
    float L = (100*  (float) letters)/ (float) words;
    float S = (100 *  (float) sentences)/ (float) words;
    //printf("L: %f\n", L);
    printf("S: %f\n", S);
    float index = 0.0588 * (float) L - 0.296 * (float) S - 15.8 ;
    //printf("Index: %f\n", index);
    index = round( index );
    //printf("Inedx near: %f\n", index);
    
    if (index < 1) printf("Before Grade 1\n");
    else if (index >= 1 && index <2) printf("Grade 1\n");
    else if (index >= 2 && index <3) printf("Grade 2\n");
    else if (index >= 3 && index <4) printf("Grade 3\n");
    else if (index >= 4 && index <5) printf("Grade 4\n");
    else if (index >= 5 && index <6) printf("Grade 5\n");
    else if (index >= 6 && index <7) printf("Grade 6\n");
    else if (index >= 7 && index <8) printf("Grade 7\n");
    else if (index >= 8 && index <9) printf("Grade 8\n");
    else if (index >= 9 && index <10) printf("Grade 9\n");
    else if (index >= 10 && index <11) printf("Grade 10\n");
    else if (index >= 11 && index <12) printf("Grade 11\n");
    else if (index >= 12 && index <13) printf("Grade 12\n");
    else if (index >= 13 && index <14) printf("Grade 13\n");
    else if (index >= 14 && index <15) printf("Grade 14\n");
    else if (index >= 15 && index <16) printf("Grade 15\n");
    else if (index >= 16 ) printf("Grade 16+\n");
    
}