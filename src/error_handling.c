/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** error_handling.c
*/

#include "my_paint.h"

bool error_handling(my_paint_t *my_paint)
{
    sfTexture *texture = NULL;
    sfFont *font = NULL;

    for (int i = 0; ASSETS[i].path; i++) {
        if (ASSETS[i].type == IMAGE) {
            texture = sfTexture_createFromFile(ASSETS[i].path, NULL);
            CHECK_NULL(texture, false);
            sfTexture_destroy(texture);
        }
        if (ASSETS[i].type == FONT) {
            font = sfFont_createFromFile(ASSETS[i].path);
            CHECK_NULL(font, false);
            sfFont_destroy(font);
        }
    }
    return true;
}
