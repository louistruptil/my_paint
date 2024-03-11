/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** button_two.c
*/

#include "my_paint.h"

void calculate_window_scale(my_paint_t *my_paint, sfVector2f *scale)
{
    sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);

    scale->x = windowSize.x / 1920.0f;
    scale->y = windowSize.y / 1080.0f;
}

void update_button_size(sfRectangleShape *rect, sfVector2f *buttonSize,
    sfVector2f scale, sfVector2f size)
{
    buttonSize->x = size.x * scale.x;
    buttonSize->y = size.y * scale.y;
    sfRectangleShape_setSize(rect, *buttonSize);
}

void update_button_position(sfRectangleShape *rect,
    sfVector2f *buttonPos, sfVector2f scale, sfVector2f pos)
{
    buttonPos->x = pos.x * scale.x;
    buttonPos->y = pos.y * scale.y;
    sfRectangleShape_setPosition(rect, *buttonPos);
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
