/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_str_isupper.c
*/

#include <stdbool.h>

/**
 * Checks if a string contains only uppercase letters.
 *
 * @param str Pointer to the constant character string to check.
 * @return True if all characters in the string are uppercase letters,
 *      false otherwise.
 */
bool my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 65 || str[i] > 90) {
            return false;
        }
    }
    return true;
}
