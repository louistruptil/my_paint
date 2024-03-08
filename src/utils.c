/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include <stdio.h>

#include "my_paint.h"

sfColor get_pixel_color(const my_paint_t *my_paint, const int x, const int y)
{
    const int pixel_index = (y * 1920 + x) * 4;
    const sfColor color = {my_paint->canva.canva_pixels[pixel_index],
        my_paint->canva.canva_pixels[pixel_index + 1],
        my_paint->canva.canva_pixels[pixel_index + 2],
        my_paint->canva.canva_pixels[pixel_index + 3]};

    return color;
}

void set_pixel_color(my_paint_t *my_paint, const int x, const int y,
    const sfColor color)
{
    const int pixel_index = (y * CANVA_WIDTH + x) * 4;

    my_paint->canva.canva_pixels[pixel_index] = color.r;
    my_paint->canva.canva_pixels[pixel_index + 1] = color.g;
    my_paint->canva.canva_pixels[pixel_index + 2] = color.b;
    my_paint->canva.canva_pixels[pixel_index + 3] = color.a;
}
