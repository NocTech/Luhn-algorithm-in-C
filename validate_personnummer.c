#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PERSONNUMMER_LENGTH 11

int calculate_control_digit(const char *personnummer)
{
    int sum = 0;
    int multiplier = 2;

    for (int i = 0; i < PERSONNUMMER_LENGTH - 1; i++)
    {
        if (personnummer[i] == '-')
        {
            continue;
        }

        int digit = personnummer[i] - '0';
        int product = digit * multiplier;

        if (product > 9)
        {
            sum += product / 10 + product % 10;
        }
        else
        {
            sum += product;
        }

        multiplier = (multiplier == 2) ? 1 : 2;
    }

    int remainder = sum % 10;
    int control_digit = (10 - remainder) % 10;

    return control_digit;
}

int validate_format(const char *personnummer)
{
    if (strlen(personnummer) != PERSONNUMMER_LENGTH)
    {
        return 0;
    }

    for (int i = 0; i < PERSONNUMMER_LENGTH; i++)
    {
        if (i == 6)
        {
            if (personnummer[i] != '-')
            {
                return 0;
            }
        }
        else if (!isdigit(personnummer[i]))
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char personnummer[PERSONNUMMER_LENGTH + 1];

    printf("Enter a personnummer (YYMMDD-NNNX): ");
    fgets(personnummer, sizeof(personnummer), stdin);

    personnummer[strcspn(personnummer, "\n")] = 0;

    if (!validate_format(personnummer))
    {
        printf("Invalid format. Please enter a personnummer in the format YYMMDD-NNNX.\n");
        return 1;
    }

    int calculated_control_digit = calculate_control_digit(personnummer);

    int entered_control_digit = personnummer[PERSONNUMMER_LENGTH - 1] - '0';

    if (calculated_control_digit == entered_control_digit)
    {
        printf("The personnummer is valid.\n");
    }
    else
    {
        printf("The personnummer is invalid.\n");
    }

    return 0;
}
