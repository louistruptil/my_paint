/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** save_canva.c
*/

#include "my_paint.h"

void destroy_color_selector(my_paint_t *my_paint)
{
    sfImage_destroy(my_paint->gui.color_selector.image);
    sfTexture_destroy(my_paint->gui.color_selector.texture);
    sfRectangleShape_destroy(my_paint->gui.color_selector.rect);
    sfRectangleShape_destroy(my_paint->gui.color_selector.selected_color);
}
