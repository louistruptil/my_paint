/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_str_isnum.c
*/

#include <stdbool.h>

/**
 * Checks if a string consists only of numeric characters (0-9).
 *
 * @param str Pointer to the constant character string to check.
 * @return True if all characters in the string are numeric, false otherwise.
 */
bool my_str_isnum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i] > 57) {
            return false;
        }
    }
    return true;
}
