/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my.h
*/

#ifndef LIBC_MY_H
    #define LIBC_MY_H

    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h>
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

// Standard
int my_putchar(char c);
int my_putstr(char *str);
int my_putnbr(int number);

// Characted
bool my_isspace(char character);
bool my_isdigit(char character);
bool my_islower(char character);
bool my_isupper(char character);
bool my_isalpha(char character);

// String
char *my_strcat(char *dest, char const *src);
char *my_strchr(char *str, char c);
char *my_strrchr(const char *str, int c);
int my_strcmp(const char *s1, const char *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char *my_revstr(char *str);
int my_atoi(char *str);
char *my_itoa(int number);
bool my_str_isalpha(char const *str);
bool my_str_islower(char const *str);
bool my_str_isnum(char const *str);
bool my_str_isprintable(char const *str);
bool my_str_isupper(char const *str);
char *my_strlowcase(char *str);
char *my_strupcase(char *str);
char **my_str_to_word_array(char *str, const char *separator);

// Memory
void *my_memcpy(void *dest, const void *src, size_t n);
void *my_memset(void *ptr, int value, size_t num);
void *my_realloc(void *ptr, size_t new_size);
void *my_calloc(size_t num_elements, size_t element_size);
void my_free_array(char **array);

// Math
int my_abs(int number);
int my_compute_square_root(int nb);
int my_compute_power_rec(int nb, int p);

// Misc
int my_array_len(char **array);

#endif //LIBC_MY_H
