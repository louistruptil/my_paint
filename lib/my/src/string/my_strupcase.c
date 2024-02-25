/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strupcase.c
*/

/**
 * Converts all lowercase characters in a string to uppercase.
 *
 * @param str Pointer to the string to be converted to uppercase.
 * @return Pointer to the string after conversion.
 */
char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 97 && str[i] <= 122)
            str[i] = str[i] - 32;
    }
    return str;
}
