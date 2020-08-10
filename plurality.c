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
    
    for (int j=0; j < candidate_count; j++){
        if (strlen(name)==strlen(candidates[j].name)){
            for (int k=0; k < (strlen(name)); k++){
                if (name[k]==candidates[j].name[k]) {
                    name_bool=true;
                }else{
                    name_bool=false;
                    break;
                }
            }
            
        }
        if (name_bool==true){
            candidates[j].votes +=1;
            return true;
            }
    
    }
    
    //for(int j=0; j < candidate_count; j++){
    //    printf("\n %s : %i", candidates[j].name,candidates[j].votes);
    //}

    
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //candidates[i].votes
    
    // TODO
    
    int v=0; //winner point
    bool more_winners=false;
    for (int i = 1; i < candidate_count; ++i) {
        if (candidates[i].votes > v){
            v = candidates[i].votes;
        }
        else if (candidates[i].votes == v && v != 0){
            more_winners=true;  
        }
    }
    
    
    //if (more_winners==true){
        for(int j = 0; j < candidate_count; j++){
            if (candidates[j].votes == v) printf("%s\n", candidates[j].name); 
        }
    
    
    //printf("%i %i",candidates[0].votes, csndidates[1.])
    //if (candidates[0].votes==candidates[1].votes)
   // printf("%s\n", candidates[0].name);
    
    return;
}

