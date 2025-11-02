#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Helpers
int check_no_space_edges(char *text);
char *prompt_for_text(char *promt);
int calc_coleman_liau_index(char *text);
void print_reading_grade(int index);

int main(void)
{
    // Prompt the user for text
    char *text = prompt_for_text("Text: ");
    // Calculate the readability index
    int index = calc_coleman_liau_index(text);
    // Print the readability grade
    print_reading_grade(index);

    return 0;
}

int calc_coleman_liau_index(char *text)
{
    // Coleman-Liau index constants
    const float L_MULTIPLIER = 0.0588;
    const float S_MULTIPLIER = 0.296;
    const float CONSTANT_OFFSET = 15.8;
    const float WORD_MULTIPLIER = 100.0;

    int letters = 0;
    int words = 0;
    int sentences = 0;

    // Track state flag for a potential sentence
    int in_potential_sentence = 0;
    // Track state flag for a potential word
    int in_word = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        // If the character is a letter
        if (isalpha(c) != 0)
        {
            // Count a new letter
            letters++;
            // Add a new potential sentence
            in_potential_sentence = 1;

            // If we aren't in the word yet, count a new word and set the flag to true
            if (in_word == 0)
            {
                words++;
                in_word = 1;
            }
        }
        else if (!(c == '\'' || c == '-' || isdigit(c)))
        {
            // If the character is not a word character, it's the end of the word and reset the flag
            in_word = 0;
        }

        // If the character is a sentence terminator, count a new sentence
        // and reset the potential sentence flag
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
            in_potential_sentence = 0;
        }
    }

    // If the potential sentence flag is set, count a missing sentence
    if (in_potential_sentence)
    {
        sentences++;
        in_potential_sentence = 0;
    }

    // If there's no text, no letters or no words, the index is 0
    if (words == 0 || letters == 0 || sentences == 0)
    {
        return 0;
    }

    // L is the average number of letters per WORD_MULTIPLIER words in the text
    float l = (float) letters / words * WORD_MULTIPLIER;
    // S is the average number of sentences per WORD_MULTIPLIER words in the text
    float s = (float) sentences / words * WORD_MULTIPLIER;

    // Calculate Coleman-Liau index: index = 0.0588 * L - 0.296 * S - 15.8
    float index = L_MULTIPLIER * l - S_MULTIPLIER * s - CONSTANT_OFFSET;

    // Return a rounded index
    return round(index);
}

void print_reading_grade(int index)
{
    // If the index is less than 1, print Before Grade 1
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    // If the index is greater than or equal to 16, print Grade 16+
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // If the index is between 1 and 16, print the grade
    else
    {
        printf("Grade %i\n", index);
    }
}

char *prompt_for_text(char *promt)
{
    char *str = NULL;

    do
    {
        str = get_string("%s", promt);
    }
    while (str == NULL || check_no_space_edges(str) == 0);

    return str;
}

int check_no_space_edges(char *text)
{
    if (!text || text[0] == '\0' || text[0] == ' ')
    {
        return 0;
    }

    // Instead of strlen() for learning purpose
    char *p = text;
    while (*p != '\0')
    {
        p++;
    }

    if (*(p - 1) == ' ')
    {
        return 0;
    }

    return 1;
}
