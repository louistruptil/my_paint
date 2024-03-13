/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** paste.c
*/

#include <stdio.h>

#include "my_paint.h"

static void calculate_copy_area(my_paint_t *my_paint, int *startPixelX,
    int *startPixelY)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(WINDOW);
    sfVector2f scale = (sfVector2f){1920.0f /
        sfRenderWindow_getSize(WINDOW).x, 1080.0f /
            sfRenderWindow_getSize(WINDOW).y};
    int mouseX = mousePos.x * scale.x;
    int mouseY = mousePos.y * scale.y;

    *startPixelX = mouseX - my_paint->tools.copy.size.x / 2;
    *startPixelY = mouseY - my_paint->tools.copy.size.y / 2;
}

static void copy_pixel(my_paint_t *my_paint, int x, int y,
    sfVector2i startPixel)
{
    int pixel = (y * 1920 + x) * 4;
    int copy_index = ((y - startPixel.y) * my_paint->tools.copy.size.x +
        (x - startPixel.x)) * 4;

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
    sfVector2i startPixel)
{
    int endPixelX = startPixel.x + my_paint->tools.copy.size.x;
    int endPixelY = startPixel.y + my_paint->tools.copy.size.y;
    int y;
    int x;

    for (y = startPixel.y; y < endPixelY; ++y) {
        for (x = startPixel.x; x < endPixelX; ++x) {
            copy_pixel(my_paint, x, y, startPixel);
        }
    }
}

void paste(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i startPixel;

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyV &&
        (sfKeyboard_isKeyPressed(sfKeyLControl) ||
            sfKeyboard_isKeyPressed(sfKeyRControl))) {
        calculate_copy_area(my_paint, &startPixel.x,
            &startPixel.y);
        copy_pixels_without_bounds(my_paint, startPixel);
    }
}
