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

void tool_paste(my_paint_t *my_paint, button_t *button)
{
    sfVector2i start_pixel;

    calculate_copy_area(my_paint, &start_pixel.x, &start_pixel.y);
    copy_pixels_without_bounds(my_paint, start_pixel);
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

static void rotate(selection_t selection, sfUint8* rotated_pixels,
    my_paint_t *my_paint, int y)
{
    int selection_width = selection.size.x;
    int selection_height = selection.size.y;
    int src_index;
    int dst_index;

    for (int x = 0; x < selection_width; ++x) {
        src_index = 4 * ((selection.pos.y + y) * 1920 + (selection.pos.x + x));
        dst_index = 4 * ((selection.pos.y + x) * 1920 + (selection.pos.x +
        selection_height - 1 - y));
        if (dst_index >= 0 && dst_index < 1920 * 1080 * 4) {
            my_memcpy(rotated_pixels + dst_index, my_paint->canva.canva_pixels
            + src_index, 4);
        }
    }
}

void rotate_selection(my_paint_t *my_paint, button_t *button)
{
    selection_t selection = my_paint->tools.selection;
    sfUint8* rotated_pixels = malloc(1920 * 1080 * 4);
    int selection_height = selection.size.y;

    for (int y = 0; y < selection_height; ++y) {
        rotate(selection, rotated_pixels, my_paint, y);
    }
    my_memcpy(my_paint->canva.canva_pixels, rotated_pixels,
    1920 * 1080 * 4);
    free(rotated_pixels);
}
