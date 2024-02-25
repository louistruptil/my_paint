/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_str_isprintable.c
*/

#include <stdbool.h>

/**
 * Checks if all characters in a string are printable.
 *
 * @param str Pointer to the constant character string to check.
 * @return True if all characters in the string are within the printable
 *      ASCII range (32-126), false otherwise.
 */
bool my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] > 126) {
            return false;
        }
    }
    return true;
}
