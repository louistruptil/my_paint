/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_array_len.c
*/

/**
 * Calculates the length of array.
 *
 * @param array Pointer to the constant array whose length is to be calculated.
 * @return The length of the array, excluding the null-terminator.
 */
int my_array_len(char **array)
{
    int count = 0;

    while (*array) {
        count++;
        array++;
    }
    return count;
}
