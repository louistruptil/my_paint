/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** btn_callback.c
*/

#include "my_paint.h"

void tool_eq_pen(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 0;
}

void tool_eq_eraser(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 1;
}

void tool_eq_picker(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 2;
}

void tool_eq_bucket(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 3;
}
