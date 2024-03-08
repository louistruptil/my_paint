/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include <stdio.h>

#include "my_paint.h"

int color_picker(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(my_paint->window.window);
    if (mouse_pos.x >= 0 && mouse_pos.x < 1920 && mouse_pos.y >= 0 && mouse_pos.y < 1080) {
        int pixel_index = (mouse_pos.y * 1920 + mouse_pos.x) * 4;
        printf("pixel_index: %d\n", pixel_index);
        printf("Color: %d %d %d\n", my_paint->canva.canva_pixels[pixel_index],
        my_paint->canva.canva_pixels[pixel_index + 1],
        my_paint->canva.canva_pixels[pixel_index + 2],
        my_paint->canva.canva_pixels[pixel_index + 3]);
    }
}