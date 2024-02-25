/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strcpy.c
*/

#include "my.h"

/**
 * Copies a source string to a destination string.
 *
 * @param dest Pointer to the destination string,
 *      which should be large enough to store the copied string.
 * @param src Pointer to the constant source string to be copied.
 * @return Pointer to the destination string after copying.
 */
char *my_strcpy(char *dest, char const *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
