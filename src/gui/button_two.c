/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** button_two.c
*/

#include "my_paint.h"

void calculate_window_scale(my_paint_t *my_paint, sfVector2f *scale)
{
    sfVector2u window_size = sfRenderWindow_getSize(WINDOW);

    scale->x = window_size.x / 1920.0f;
    scale->y = window_size.y / 1080.0f;
}

void update_button_size(sfRectangleShape *rect, sfVector2f *button_size,
    sfVector2f scale, sfVector2f size)
{
    button_size->x = size.x * scale.x;
    button_size->y = size.y * scale.y;
    sfRectangleShape_setSize(rect, *button_size);
}

void update_button_position(sfRectangleShape *rect,
    sfVector2f *button_pos, sfVector2f scale, sfVector2f pos)
{
    button_pos->x = pos.x * scale.x;
    button_pos->y = pos.y * scale.y;
    sfRectangleShape_setPosition(rect, *button_pos);
}

void destroy_button(button_t *button)
{
    sfRectangleShape_destroy(button->rect);
    if (button->text && button->font) {
        sfFont_destroy(button->font);
        sfText_destroy(button->text);
    }
    if (button->img_texture)
        sfTexture_destroy(button->img_texture);
    free(button);
}
