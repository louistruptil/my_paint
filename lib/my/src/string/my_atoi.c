/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_atoi.c
*/

#include "my.h"
#include <limits.h>

/**
 * Converts a string to an integer.
 *
 * @param str Null-terminated string to convert.
 * @return Integer value, 0 for non-numeric, INT MAX/MIN on overflow/underflow.
 */
int my_atoi(char *str)
{
    int result = 0;
    bool is_negative = false;
    int digit;

    if (!str)
        return 0;
    while (my_isspace(*str))
        str++;
    if (*str == '-' || *str == '+') {
        is_negative = (*str == '-') ? true : false;
        str++;
    }
    for (; my_isdigit(*str); str++) {
        digit = *str - '0';
        if (result > INT_MAX / 10 ||
        (result == INT_MAX / 10 && digit > INT_MAX % 10))
            return is_negative ? INT_MIN : INT_MAX;
        result = 10 * result + digit;
    }
    return is_negative ? result * -1 : result;
}
