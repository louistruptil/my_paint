/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_isalpha.c
*/

#include <stdbool.h>

/**
 * Determines if a character is alphanumeric.
 *
 * @param character Character to test.
 * @return true if alphanumeric, false otherwise.
 */
bool my_isalpha(char character)
{
    return (character >= 'a' && character <= 'z') ||
        (character >= 'A' && character <= 'Z') ? true : false;
}
