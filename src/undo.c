/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void undo_act(my_paint_t *my_paint, button_t *button)
{
    if (my_paint->undoredo.actual > 0) {
        if (my_paint->undoredo.canva_pixels[my_paint->undoredo.actual]
        == NULL) {
            my_paint->undoredo.canva_pixels[my_paint->undoredo.actual] =
            malloc(1920 * 1080 * 4);
        }
        my_memcpy(my_paint->undoredo.canva_pixels[my_paint->undoredo.actual],
        my_paint->canva.canva_pixels, 1920 * 1080 * 4);
        my_paint->undoredo.actual--;
        my_memcpy(my_paint->canva.canva_pixels,
        my_paint->undoredo.canva_pixels[my_paint->undoredo.actual],
        1920 * 1080 * 4);
    } else {
        my_putstr("There's nothing to undo\n");
    }
}

void btn_undo(my_paint_t *my_paint)
{
    my_paint->gui.button[12] = create_button((button_options_t) {
        {20, 670},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/undo.png"
    }, undo_act, NULL);
}
