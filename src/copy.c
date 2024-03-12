/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** copy_paste.c
*/

#include <stdio.h>

#include "my_paint.h"

static void clear_copy(my_paint_t *my_paint)
{
    for (int i = 0; i < 1920 * 1080 * 4; i++) {
        my_paint->tools.copy.canva[i] = 0;
        my_paint->tools.copy.canva[i + 1] = 0;
        my_paint->tools.copy.canva[i + 2] = 0;
        my_paint->tools.copy.canva[i + 3] = 0;
    }
}

static void copy_single_pixel(my_paint_t *my_paint, int pixel_x,
    int pixel_y, int copy_index)
{
    int index = (pixel_x + pixel_y * 1920) * 4;

    if (pixel_x >= 0 && pixel_x < 1920 && pixel_y >= 0 && pixel_y < 1080) {
        my_paint->tools.copy.canva[copy_index] =
            my_paint->canva.canva_pixels[index];
        my_paint->tools.copy.canva[copy_index + 1] =
            my_paint->canva.canva_pixels[index + 1];
        my_paint->tools.copy.canva[copy_index + 2] =
            my_paint->canva.canva_pixels[index + 2];
        my_paint->tools.copy.canva[copy_index + 3] =
            my_paint->canva.canva_pixels[index + 3];
    } else {
        my_paint->tools.copy.canva[copy_index] = 0;
        my_paint->tools.copy.canva[copy_index + 1] = 0;
        my_paint->tools.copy.canva[copy_index + 2] = 0;
        my_paint->tools.copy.canva[copy_index + 3] = 0;
    }
}

static void copy_pixels_from_selection(my_paint_t *my_paint,
    selection_t select)
{
    int copy_index = 0;

    for (int y = 0; y < select.size.y; y++) {
        for (int x = 0; x < select.size.x; x++) {
            copy_single_pixel(my_paint, select.pos.x + x, select.pos.y + y,
                copy_index);
            copy_index += 4;
        }
    }
}

static void copy_selection_from_canvas(my_paint_t *my_paint,
    selection_t select)
{
    my_paint->tools.copy.pos = select.pos;
    my_paint->tools.copy.size = select.size;
    clear_copy(my_paint);
    copy_pixels_from_selection(my_paint, select);
}

void copy_selection(my_paint_t *my_paint, sfEvent event)
{
    selection_t selection = my_paint->tools.selection;
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyC &&
        (sfKeyboard_isKeyPressed(sfKeyLControl) ||
        sfKeyboard_isKeyPressed(sfKeyRControl))) {
        adjust_selection_coordinates(&selection, window_size);
        copy_selection_from_canvas(my_paint, selection);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyX &&
        (sfKeyboard_isKeyPressed(sfKeyLControl) ||
        sfKeyboard_isKeyPressed(sfKeyRControl))) {
        adjust_selection_coordinates(&selection, window_size);
        copy_selection_from_canvas(my_paint, selection);
        delete_selection_from_canvas(my_paint, selection);
    }
}
