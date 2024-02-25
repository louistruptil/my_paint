/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_revstr.c
*/

#include "my.h"

/**
 * Reverses a string in place.
 *
 * @param str Pointer to the string to be reversed.
 * @return Pointer to the reversed string.
 */
char *my_revstr(char *str)
{
    char temp_str;
    int len = my_strlen(str);
    int j = len - 1;

    for (int i = 0; i < j; i++) {
        temp_str = str[i];
        str[i] = str[j];
        str[j] = temp_str;
        j--;
    }
    return str;
}
