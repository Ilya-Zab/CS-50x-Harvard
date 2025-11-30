#include <cs50.h>
#include <ctype.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
bool str_equal_nocase(char *str, char *str2);
int find_highest_vote_count(candidate *arr, int size);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (str_equal_nocase(candidates[i].name, name))
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_count = find_highest_vote_count(candidates, candidate_count);

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_count)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

int find_highest_vote_count(candidate *arr, int size)
{
    if (size <= 0)
    {
        return -1;
    }

    int max = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i].votes > max)
        {
            max = arr[i].votes;
        }
    }

    return max;
}

bool str_equal_nocase(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        char c1 = *str1;
        char c2 = *str2;

        if (tolower(c1) != tolower(c2))
        {
            return false;
        }

        str1++;
        str2++;
    }

    // if one is not at the end, the lengths differ
    if (*str1 != '\0' || *str2 != '\0')
    {
        return false;
    }

    return true;
}
