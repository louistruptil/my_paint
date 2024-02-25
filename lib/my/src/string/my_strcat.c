/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strcat.c
*/

#include "my.h"

/**
 * Concatenates a source string to the end of a destination string.
 *
 * @param dest Pointer to the destination string,
 *      which should have enough space for the concatenation.
 * @param src Pointer to the constant source string to be appended to dest.
 * @return Pointer to the destination string after concatenation.
 */
char *my_strcat(char *dest, char const *src)
{
    int len = my_strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    return dest;
}
