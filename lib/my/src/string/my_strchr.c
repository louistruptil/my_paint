/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strchr.c
*/

#include "my.h"

/**
 * Searches for the first occurrence of a character in a string.
 *
 * @param str Pointer to the string to be searched.
 * @param c The character to search for.
 * @return Pointer to the first occurrence of c in str,
 *      or NULL if c is not found.
 */
char *my_strchr(char *str, char c)
{
    while (*str) {
        if (*str == c)
            return str;
        str++;
    }
    return NULL;
}
