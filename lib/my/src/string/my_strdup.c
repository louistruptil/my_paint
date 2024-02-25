/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strdup.c
*/

#include "my.h"

/**
 * Duplicates a string by allocating memory for a new copy.
 *
 * @param src Pointer to the constant source string to be duplicated.
 * @return Pointer to the newly allocated string, which is a duplicate of src.
 */
char *my_strdup(char const *src)
{
    char *str;

    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    my_strcpy(str, src);
    return str;
}
