/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_str_islower.c
*/

#include <stdbool.h>

/**
 * Checks if a string contains only lowercase letters.
 *
 * @param str Pointer to the constant character string to check.
 * @return True if all characters in the string are lowercase letters,
 *      false otherwise.
 */
bool my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 97 || str[i] > 122) {
            return false;
        }
    }
    return true;
}
