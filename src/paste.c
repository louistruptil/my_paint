/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** paste.c
*/

#include <stdio.h>

#include "my_paint.h"

static void calculate_copy_area(my_paint_t *my_paint, int *start_pixelX,
    int *start_pixelY)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(WINDOW);
    sfVector2f scale = (sfVector2f){1920.0f /
        sfRenderWindow_getSize(WINDOW).x, 1080.0f /
            sfRenderWindow_getSize(WINDOW).y};
    int mouseX = mousePos.x * scale.x;
    int mouseY = mousePos.y * scale.y;

    *start_pixelX = mouseX - my_paint->tools.copy.size.x / 2;
    *start_pixelY = mouseY - my_paint->tools.copy.size.y / 2;
}

static void copy_pixel(my_paint_t *my_paint, int x, int y,
    sfVector2i start_pixel)
{
    int pixel = (y * 1920 + x) * 4;
    int copy_index = ((y - start_pixel.y) * my_paint->tools.copy.size.x +
        (x - start_pixel.x)) * 4;

    if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
        return;
    my_paint->canva.canva_pixels[pixel] =
        my_paint->tools.copy.canva[copy_index];
    my_paint->canva.canva_pixels[pixel + 1] =
        my_paint->tools.copy.canva[copy_index + 1];
    my_paint->canva.canva_pixels[pixel + 2] =
        my_paint->tools.copy.canva[copy_index + 2];
    my_paint->canva.canva_pixels[pixel + 3] =
        my_paint->tools.copy.canva[copy_index + 3];
}

static void copy_pixels_without_bounds(my_paint_t *my_paint,
    sfVector2i start_pixel)
{
    int end_pixel_x = start_pixel.x + my_paint->tools.copy.size.x;
    int end_pixel_y = start_pixel.y + my_paint->tools.copy.size.y;
    int y;
    int x;

    for (y = start_pixel.y; y < end_pixel_y; ++y) {
        for (x = start_pixel.x; x < end_pixel_x; ++x) {
            copy_pixel(my_paint, x, y, start_pixel);
        }
    }
}

void paste(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i start_pixel;

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyV &&
        (sfKeyboard_isKeyPressed(sfKeyLControl) ||
            sfKeyboard_isKeyPressed(sfKeyRControl))) {
        calculate_copy_area(my_paint, &start_pixel.x,
            &start_pixel.y);
        copy_pixels_without_bounds(my_paint, start_pixel);
    }
}
