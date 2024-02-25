/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strstr.c
*/

#include "my.h"

/**
 * Locates a substring in a string.
 *
 * @param str Pointer to the string to be searched.
 * @param to_find Pointer to the substring to find in str.
 * @return Pointer to the first occurrence of to_find in str,
 *      or NULL if to_find is not found.
 */
char *my_strstr(char *str, char const *to_find)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        if (my_strncmp(&str[i], to_find, my_strlen(to_find)) == 0)
            return &str[i];
    return NULL;
}
