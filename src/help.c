/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

void create_help(my_paint_t *my_paint)
{
    sfTexture* texture = sfTexture_createFromFile("assets/help.png", NULL);
    sfSprite* sprite = sfSprite_create();
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2u texture_size = sfTexture_getSize(texture);
    float scale_x = 0.8f * window_size.x / texture_size.x;
    float scale_y = 0.8f * window_size.y / texture_size.y;
    float pos_x;
    float pos_y;

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, (sfVector2f){scale_x, scale_y});
    pos_x = (window_size.x - scale_x * texture_size.x) / 2;
    pos_y = (window_size.y - scale_y * texture_size.y) / 2;
    sfSprite_setPosition(sprite, (sfVector2f){pos_x, pos_y});
    my_paint->help.sprite = sprite;
    my_paint->help.texture = texture;
}

void display_help(my_paint_t *my_paint)
{
    if (my_paint->help.display_help == 1) {
        update_help_position(my_paint);
        sfRenderWindow_drawSprite(my_paint->window.window,
        my_paint->help.sprite, NULL);
    }
}

static void update_help_position(my_paint_t *my_paint)
{
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f help_size = {window_size.x * 0.8f, window_size.y * 0.8f};
    sfVector2f help_position = {window_size.x / 2.0f - help_size.x / 2.0f,
        window_size.y / 2.0f - help_size.y / 2.0f};
    sfVector2u texture_size = sfTexture_getSize(my_paint->help.texture);
    sfVector2f scale_factor = {help_size.x / texture_size.x, help_size.y
    / texture_size.y};

    sfSprite_setScale(my_paint->help.sprite, scale_factor);
    sfSprite_setPosition(my_paint->help.sprite, help_position);
}

void help_btn_act(my_paint_t *my_paint, button_t *button)
{
    if (my_paint->help.display_help == 0)
        my_paint->help.display_help = 1;
    else
        my_paint->help.display_help = 0;
}
