/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_compute_power_rec.c
*/

/**
 * @brief Computes the power of a number recursively.
 *
 * @param nb The base number.
 * @param p The exponent.
 * @return The result of nb raised to the power of p.
 * Returns 1 if p is 0, 0 if p is negative or nb exceeds integer limits.
 */
int my_compute_power_rec(int nb, int p)
{
    int a = nb;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    if (a > __INT_MAX__)
        return 0;
    return (a * my_compute_power_rec(a, p - 1));
}
