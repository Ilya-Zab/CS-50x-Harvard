#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// --- Helpers ---
char *prompt_user_for_text(void);
int validate_key(char *key);
char *substitute_text(char *key, char *text);

// --- Constants ---
#define ARG_LEN 2
#define ALPHABET_LEN 26

int main(int argc, char **argv)
{
    if (argc != ARG_LEN)
    {
        printf("Error: missing or too many arguments.\n");
        printf("Usage: %s <26-letter key>\n", argv[0]);
        return 1;
    }

    char *key = argv[1];

    if (validate_key(key) == 0)
    {
        printf("Invalid key: must be 26 unique alphabetical characters.\n");
        return 1;
    }

    char *text = prompt_user_for_text();

    if (text == NULL)
    {
        printf("Error: plaintext must be a non-empty string.\n");
        return 1;
    }

    char *cipher_text = substitute_text(key, text);

    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

// --- Helpers ---

// Returns 1(true) if the key is valid and 0(false) otherwise
int validate_key(char *key)
{
    if (strlen(key) != ALPHABET_LEN)
    {
        return 0;
    }

    // Bitmap array to track which letters have appeared
    int seen[ALPHABET_LEN] = {0};

    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        char c = key[i];

        // Each character must be alphabetic
        if (isalpha(c) == 0)
        {
            return 0;
        }

        // Map character to index 0-25
        c = tolower(c);
        int index = c - 'a';

        // Duplicate detected
        if (seen[index] == 1)
        {
            return 0;
        }

        seen[index] = 1;
    }

    return 1;
}

// Prompts the user for input and returns a string on success, or NULL if input failed/empty
char *prompt_user_for_text(void)
{
    char *key = get_string("plaintext: ");

    if (key == NULL || key[0] == '\0')
    {
        return NULL;
    }

    return key;
}

// Applies a substitution 26 letters key to the text in-place (text is modified directly)
char *substitute_text(char *key, char *text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        if (isalpha(c) != 0)
        {
            int index = tolower(c) - 'a';
            char cipher_c = key[index];

            if (isupper(c))
            {
                text[i] = toupper(cipher_c);
            }
            else
            {
                text[i] = tolower(cipher_c);
            }
        }
    }

    return text;
}
