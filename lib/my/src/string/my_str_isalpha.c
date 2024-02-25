/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_str_isalpha.c
*/

#include <stdbool.h>

/**
 * Checks if a string contains only alphabetic characters.
 *
 * @param str Pointer to the constant character string to check.
 * @return True if all characters in the string are alphabetic,
 *      false otherwise.
 */
bool my_str_isalpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < 65 || str[i] > 90) && (str[i] < 97 || str[i] > 122)) {
            return false;
        }
    }
    return true;
}
