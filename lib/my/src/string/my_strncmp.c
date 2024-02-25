/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strncmp.c
*/

/**
 * Compares up to n characters of two strings lexicographically.
 *
 * @param s1 Pointer to the first string to be compared.
 * @param s2 Pointer to the second string to be compared.
 * @param n The maximum number of characters to compare.
 * @return An integer greater than, equal to, or less than 0,
 * if the first n characters of s1 are found,
 * respectively, to be greater than, to match,
 * or be less than the first n characters of s2.
 */
int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] == s2[i] && s1[i] != '\0')
        i++;
    if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
        return 0;
    if (s1[i] - s2[i] > 0)
        return 1;
    if (s1[i] - s2[i] < 0)
        return -1;
    return 0;
}
