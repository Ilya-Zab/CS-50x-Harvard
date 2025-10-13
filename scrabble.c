#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter A-Z
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Helper function prototypes
char *prompt_for_string(char *promt);
int compute_score(char *word);

int main(void)
{
    // Prompts playes for a string input
    char *player_1 = prompt_for_string("Player 1: ");
    char *player_2 = prompt_for_string("Player 2: ");

    // Computes the scrabble-style score for both players
    int score_1 = compute_score(player_1);
    int score_2 = compute_score(player_2);

    // Compares the players scores and prints the winner or tie
    if (score_1 > score_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score_1 < score_2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

// Prompts a player for a string input
char *prompt_for_string(char *promt)
{
    char *str = NULL;

    do
    {
        str = get_string("%s", promt);
    }
    while (str == NULL || strlen(str) == 0);

    return str;
}

// Computes the scrabble-style score for a word
int compute_score(char *word)
{
    int score = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = tolower(word[i]);

        // Checks if the character is alphabetic
        // The same as c >= 'a' && c <= 'z'
        if (isalpha(c) != 0)
        {
            score += POINTS[c - 'a'];
        }
    }

    return score;
}
