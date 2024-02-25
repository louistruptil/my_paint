/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strlowcase.c
*/

/**
 * Converts all uppercase characters in a string to lowercase.
 *
 * @param str Pointer to the string to be converted to lowercase.
 * @return Pointer to the string after conversion.
 */
char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
    }
    return str;
}
