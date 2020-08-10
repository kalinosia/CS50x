#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

string winner;
//int min=0;

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
//===============================================================VOTE \|/
    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();//######################################
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero!!!!!!!!!!
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    bool exist_candidate=false;
    for (int j=0; j < candidate_count; j++){
        if (strlen(name)==strlen(candidates[j].name)){
            if (strcmp(candidates[j].name, name)==0) {
                exist_candidate=true;
                preferences[voter][rank]=j;
            }
        }
    }
   
    if (exist_candidate==true) return true; 
    else return false;
    
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    /*
   //vote for candidate
    for (int i=0; i < voter_count; i++){   
        for (int j=0; j < candidate_count; j++){
            if (preferences[i][0]==j && !(candidates[j].eliminated)){
                candidates[j].votes+=1;    
            }
        }
    }
    
    //kandydat ma większość
    for (int j=0; j < candidate_count; j++) {
        if ((candidates[j].votes >= voter_count/2+1)&& candidates[j].eliminated==false){
            winner=candidates[j].name;
        } 
    }
    
    for (int k=0; k < candidate_count; k++){
        if (candidates[k].eliminated==true){
            for(int l=0; l < voter_count; l++){
                if (preferences[l][0]==k){
                    candidates[k].votes-=1;
                    
                    //for (int m=0; m < candidate_count; m++){
                        for (int n=0; n < candidate_count; n++){
                            if (preferences[l][1]==n && candidates[n].eliminated==false){
                                candidates[n].votes+=1; 
                                break;
                            }
                        }
                    //}
                
                }
            }
        }
    }
   */
   bool find=false;
    for (int i=0; i < voter_count; i++){
        find=false;
        for (int k=0; k < candidate_count; k++){ //k only when candidates eliminated
            for (int j=0; j < candidate_count; j++){
                if (preferences[i][k]==j && !(candidates[j].eliminated)){
                    candidates[j].votes+=1;
                    find=true;
                }
                else if(preferences[i][k]==j){
                    break;
                    find=false;
                }
            }
            if (find==true) break;
        }
    }
    for (int j=0; j < candidate_count; j++) {
        if ((candidates[j].votes >= voter_count/2+1)&& candidates[j].eliminated==false){
            winner=candidates[j].name;
        } 
    }
    
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
      for (int j=0; j < candidate_count; j++) {
        if ((candidates[j].votes >= voter_count/2+1)&& candidates[j].eliminated==false){
            winner=candidates[j].name;
            printf("%s\n", winner );
            return true;
        } 
    }
    
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minimum=0;
    for (int i=0; i < candidate_count; i++){
        if(candidates[i].votes <= minimum && !(candidates[i].eliminated)) minimum=candidates[i].votes;
    }
    return minimum;
    //return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    
    bool tie=false;
    for (int i=0; i < candidate_count; i++){
        if(candidates[i].eliminated) break;
        if (!(candidates[i].votes==min)){
            tie=false; //for calm mind
            return false;
        }
        else tie=true;
    }
    if (tie==true) return true;
    else return false;
    
}


// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for ( int i=0; i<candidate_count; i++){
        if (candidates[i].votes==min && candidates[i].eliminated==false){
            candidates[i].eliminated=true;
        }
    }
    min=0;
    return;
}
