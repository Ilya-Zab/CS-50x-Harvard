#include <cs50.h>
#include <stdio.h>

void validate_credit_card(long card_number);
long get_credit_card_number();
int validate_checksum(long card_number);
int get_starting_digits(long number, int count, int len);
int digit_count(long digits);

// Define the constants for the card lengths and prefixes
static const int LEN_VISA_SHORT = 13;
static const int LEN_AMEX = 15;
static const int LEN_VISA_LONG = 16;
static const int LEN_MC = 16;

static const int PREFIX_VISA = 4;
static const int PREFIX_AMEX_1 = 34;
static const int PREFIX_AMEX_2 = 37;
static const int PREFIX_MC_MIN = 51;
static const int PREFIX_MC_MAX = 55;

int main()
{
    long card_number = get_credit_card_number();
    validate_credit_card(card_number);
    return 0;
}

void validate_credit_card(long card_number)
{
    // If the card number is negative, return 0 - not valid
    if (card_number < 0)
    {
        printf("INVALID\n");
        return;
    }

    int is_checksum_valid = validate_checksum(card_number);

    // If the checksum is not valid, return INVALID
    if (!is_checksum_valid)
    {
        printf("INVALID\n");
        return;
    }

    int card_number_len = digit_count(card_number);

    if (!(card_number_len == LEN_VISA_SHORT || card_number_len == LEN_AMEX ||
          card_number_len == LEN_VISA_LONG))
    {
        printf("INVALID\n");
        return;
    }

    int starting_digits = get_starting_digits(card_number, 2, card_number_len);
    int first_digit = get_starting_digits(card_number, 1, card_number_len);

    if (card_number_len == LEN_AMEX &&
        (starting_digits == PREFIX_AMEX_1 || starting_digits == PREFIX_AMEX_2))
    {
        printf("AMEX\n");
        return;
    }

    if (card_number_len == LEN_MC &&
        (starting_digits >= PREFIX_MC_MIN && starting_digits <= PREFIX_MC_MAX))
    {
        printf("MASTERCARD\n");
        return;
    }

    if ((card_number_len == LEN_VISA_SHORT || card_number_len == LEN_VISA_LONG) &&
        first_digit == PREFIX_VISA)
    {
        printf("VISA\n");
        return;
    }

    printf("INVALID\n");
}

long get_credit_card_number()
{
    long card_number = 0;

    while (card_number <= 0)
    {
        card_number = get_long("Enter your card number: ");
    }

    return card_number;
}

int validate_checksum(long card_number)
{
    // If the card number is negative, return 0 - not valid
    if (card_number < 0)
    {
        return 0;
    }

    int sum = 0;
    int is_second_digit = 0;

    while (card_number > 0)
    {
        int digit = card_number % 10;

        if (is_second_digit)
        {
            digit *= 2;

            if (digit > 9)
            {
                digit = digit % 10 + digit / 10;
            }
        }

        sum += digit;
        card_number /= 10;
        is_second_digit = !is_second_digit;
    }

    return (sum % 10) == 0;
}

int get_starting_digits(long number, int count, int len)
{
    if (len <= count)
    {
        return (int) number;
    }

    int shift = len - count;

    while (shift-- > 0)
    {
        number /= 10;
    }

    return (int) number;
}

int digit_count(long n)
{
    if (n == 0)
    {
        return 1;
    }

    if (n < 0)
    {
        n = -n;
    }

    int count = 0;

    while (n > 0)
    {
        n /= 10;
        count++;
    }

    return count;
}
