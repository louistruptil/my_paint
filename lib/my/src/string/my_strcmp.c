/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strcmp.c
*/

#include "my.h"

/**
 * Compares two strings lexicographically.
 *
 * @param s1 Pointer to the first string to be compared.
 * @param s2 Pointer to the second string to be compared.
 * @return An integer greater than, equal to, or less than 0, if s1 is found,
 *         respectively, to be greater than, to match, or be less than s2.
 */
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0')
        i++;
    if (s1[i] - s2[i] > 0)
        return 1;
    if (s1[i] - s2[i] < 0)
        return -1;
    if (s1[i] - s2[i] == 0)
        return 0;
    return 0;
}
