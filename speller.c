// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype - function declaration
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3) //must be 2 or 3 argc?
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Structures for timing data
    struct rusage before, after; //before is rusage type, and after

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0; //time = 0 declaration

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY; //if pointer = arg3 then argc[1] else DICTIONARY

    // Load dictionary
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);//time loaded dictionary

    // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate time to load dictionary
    time_load = calculate(&before, &after);

    // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];//if we've got 3 arg then argv[2] if not argv[1] (is text)
    FILE *file = fopen(text, "r"); //open read file
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;//reset to 0
    char word[LENGTH + 1];//word lenght = max lenght 

    // Spell-check each word in text
    for (int c = fgetc(file); c != EOF; c = fgetc(file)) //fget() get the next u. char; EOF end of file; get next
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0)) //we need only alpphabet and ' 
        {
            // Append character to word
            word[index] = c; //word[0]=char that we read nonononononon because index>0 why????????????
            index++; //word[1]

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH) //if index>45 char
            {
                // Consume remainder of alphabetical string 
                while ((c = fgetc(file)) != EOF && isalpha(c)); //stream when not end and alhapethical

                // Prepare for new word
                index = 0; //new word
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c)) //dont want number / digits
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c)); //stream continue 

            // Prepare for new word
            index = 0; //word[0]
        }

        // We must have found a whole word
        else if (index > 0) //if we start word but not alphabetical and ' and not number so space? - ! ..
        {
         
            // Terminate current word
            word[index] = '\0'; //end of word

            // Update counter
            words++; //we got word

            // Check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);//check word
            getrusage(RUSAGE_SELF, &after);

            // Update benchmark
            time_check += calculate(&before, &after);//checking word time

            // Print word if misspelled
            if (misspelled) //if word is misspelled
            {
                printf("%s\n", word);///########################################################
                misspellings++;
            }

            // Prepare for next word
            index = 0; //next word
        }
    }

    // Check whether there was an error
    if (ferror(file)) //always chceck if error in read file
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Close text
    fclose(file); //at the end close file

    // Determine dictionary's size
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calculate time to determine dictionary's size
    time_size = calculate(&before, &after); 

    // Unload dictionary
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Abort if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calculate time to unload dictionary
    time_unload = calculate(&before, &after);

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL) 
    {
        return 0.0;
    }
    else
    { // (Difference between the user CPU time used after and before + Difference between the system CPU time used after and before)/ 1000000.0 to second
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) - //user CPU time used in seconds + user CPU time used in microseconds
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
