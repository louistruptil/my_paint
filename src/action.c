/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/
#include "my_paint.h"

static int draw_cmd(my_paint_t *my_paint, sfEvent event)
{

    my_paint->tools.rgba[0] = 0;
    my_paint->tools.rgba[1] = 0;
    my_paint->tools.rgba[2] = 0;
    my_paint->tools.rgba[3] = 255;
    drawing_loop(my_paint, event);
}

static int ereased_cmd(my_paint_t *my_paint, sfEvent event)
{

    my_paint->tools.rgba[0] = 255;
    my_paint->tools.rgba[1] = 255;
    my_paint->tools.rgba[2] = 255;
    my_paint->tools.rgba[3] = 255;
    drawing_loop(my_paint, event); 
}

void do_select_action(my_paint_t *my_paint, sfEvent event)
{
    if (my_paint->tools.actual_tools == 0)
        draw_cmd(my_paint, event);
    if (my_paint->tools.actual_tools == 1)
        ereased_cmd(my_paint, event);
}