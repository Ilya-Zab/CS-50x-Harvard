#include <cs50.h>
#include <stdio.h>

#define GAP_WIDTH 2

int prompt_int_between(int min, int max);
void print_repeated_char(char c, int repeats);
void print_row(int row, int height, int gap_width);

int main()
{
    int height = prompt_int_between(1, 8);

    for (int i = 0; i < height; i++)
    {
        print_row(i, height, GAP_WIDTH);
    }

    return 0;
}

// Prompt the user for an integer between a given minimum and maximum value
int prompt_int_between(int min, int max)
{
    if (min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }

    int user_input;

    do
    {
        user_input = get_int("Enter a number between %d and %d: ", min, max);
    }
    while (user_input < min || user_input > max);

    return user_input;
}

// Print a row of the pyramid
void print_row(int row, int height, int gap_width)
{
    int left_spaces = height - row - 1;
    int blocks = row + 1;

    print_repeated_char(' ', left_spaces);
    print_repeated_char('#', blocks);
    print_repeated_char(' ', gap_width);
    print_repeated_char('#', blocks);
    putchar('\n');
}

// Print a character a given number of times
void print_repeated_char(char c, int repeats)
{
    for (int i = 0; i < repeats; i++)
    {
        putchar(c);
    }
}
