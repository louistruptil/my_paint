/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_itoa.c
*/

#include "my.h"
#include <stdbool.h>
#include <limits.h>

static void recursive_itoa(int number, char *buffer, int *index)
{
    if (number <= -10 || number >= 10)
        recursive_itoa(number / 10, buffer, index);
    buffer[*index] = '0' + my_abs(number % 10);
    (*index)++;
}

/**
 * Converts an integer to a string.
 *
 * @param number Integer to convert.
 * @return Pointer to a string representing the integer.
 */
char *my_itoa(int number)
{
    char *buffer = malloc(12);
    int index = 0;
    bool is_negative = false;

    if (number <= INT_MIN || number >= INT_MAX)
        return number <= INT_MIN ? "-2147483648" : "2147483647";
    if (number < 0) {
        is_negative = true;
        number = -number;
    }
    recursive_itoa(number, buffer, &index);
    if (is_negative) {
        buffer = my_revstr(buffer);
        buffer[index] = '-';
        index++;
        buffer = my_revstr(buffer);
    }
    buffer[index] = '\0';
    return buffer;
}
