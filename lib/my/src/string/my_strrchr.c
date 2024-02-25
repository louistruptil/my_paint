/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strrchr.c
*/

#include "my.h"

/**
 * Searches for the last occurrence of a character in a string.
 *
 * @param str Pointer to the string to be searched.
 * @param c The character to search for.
 * @return Pointer to the last occurrence of c in str,
 *      or NULL if c is not found.
 */
char *my_strrchr(const char *str, int c)
{
    const char *last = NULL;

    while (*str) {
        if (*str == c)
            last = str;
        str++;
    }
    return (char *)last;
}
