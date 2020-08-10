#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool name_bool=false;
    //char name_char= (char) name;
    for (int j=0; j < candidate_count; j++){
            if(!(name[0]==candidates[j].name[0])) j++;
            else{
                for (int k=0; k < (strlen(name)); k++){
                if (name[k]==candidates[j].name[k]) name_bool=true;
                else name_bool=false;
            }
            if (name_bool==true){
                candidates[j].votes +=1;
                return true;
            }
        }
    }

    //printf("\n%s  wypisane \n", name);
    //printf("\n %c wypisana litera \n", name[1]);
    //printf("\n%s \n", candidates[0].name);
    
    // TODO
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //candidates[i].votes
    // TODO
    for (int i = 1; i < candidate_count; ++i) {
        if (candidates[0].votes < candidates[i].votes){
            candidates[0].votes = candidates[i].votes;
    }}

    printf("Largest element = %s", candidates[0].name);
    
    return;
}

