/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_abs.c
*/

/**
 * Computes the absolute value of an integer.
 *
 * @param number Integer to find the absolute value of.
 * @return Absolute value of number. Undefined if number is INT_MIN.
 */
int my_abs(int number)
{
    return (number < 0) ? -number : number;
}
