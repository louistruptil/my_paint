/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_compute_square_root.c
*/

/**
 * @brief Computes the square root of a number.
 *
 * @param nb The number to find the square root of.
 * @return The square root of nb if it is a perfect square,
 * otherwise returns 0. Returns 1 if nb is 1.
 */
int my_compute_square_root(int nb)
{
    if (nb == 1)
        return 1;
    for (int i = 0; i < nb; i++) {
        if (i > __INT_MAX__)
            return 0;
        if (i * i == nb && (i != nb))
            return i;
    }
    return 0;
}
