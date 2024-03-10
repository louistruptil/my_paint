/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

int main_loop(my_paint_t *my_paint)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        event_loop(WINDOW, my_paint->window.event, my_paint);
        display(my_paint);
    }
}