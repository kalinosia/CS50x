#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes----------------------------------------------------------
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
     bool exist_candidate=false;
    for (int j=0; j < candidate_count; j++){
        if (strlen(name)==strlen(candidates[j])){
            if (strcmp(candidates[j], name)==0) {
                exist_candidate=true;
                ranks[rank]=j;
                //preferences[voter][rank]=j;///////////////////////////////?
            }
        }
    }
   
    if (exist_candidate==true) return true; 
    else return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i=0; i < candidate_count; i++){
        for (int j=0; j < candidate_count; j++){
            for (int k=0; k < candidate_count; k++){
                for (int l=0; l < candidate_count; l++){
                    if (ranks[i]==j && ranks[k]==l  && i<k){
                    preferences[j][l]+=1;
                    }
                }
            }
        }
    }
    
    
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int z=0;
    int tied=0; //tied if 1 or to or something then less pair 
    
    int i=0;   
        for (int j=z; j < candidate_count-z; j++){
            for (int k=z+1; k < candidate_count-z-1; k++){
                    if (preferences[j][k] > preferences[k][j]){
                        pairs[i].winner=j;
                        pairs[i].loser=k; 
                        i++;
                    }
                    else if (preferences[k][j] > preferences[j][k]){
                        pairs[i].winner=k;
                        pairs[i].loser=j;
                        i++;
                    }
                    else {//tied
                        tied+=1;
                    }
            }
            z++;
        }
        
    pair_count-=tied;
     
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int max;
    int s=0;//sorted pairs from left to right array
    pair pairSort;
    for (int i=0; i < pair_count; i++){
            for (int j=s; j < pair_count-s; j++){
                
                if(preferences[pairs[j].winner][pairs[j].loser] >= max){
                  max=preferences[pairs[j].winner][pairs[j].loser];  
                } 
            }
            if(preferences[pairs[i].winner][pairs[i].loser] >= max){
                pairSort=pairs[s];
                pairs[s]=pairs[i];
                pairs[i]=pairSort;
                //pair[s]; ZWOLNIĆ DANĄ??
                s++;
            }
    }
            
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO     bool locked[MAX][MAX];
    for (int i=0; i < pair_count; i++){
        if(!(locked[pairs[i].loser][pairs[i].winner]==true && locked[pairs[i+1].loser][pairs[i+1].winner]==true)){
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
        else locked[pairs[i].winner][pairs[i].loser]=false;
    }
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i=0; i < pair_count; i++){
        if (locked[pairs[i].loser][pairs[i].winner]==false){
            printf("%s\n", candidates[pairs[i].winner]);
        }
    }
    return;
}

