/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include <stdio.h>
#include "my_paint.h"

static void update_popup2pos(my_paint_t *my_paint, sfVector2f text_position,
    sfVector2u window_size, sfVector2f text_position2)
{
    sfFloatRect text_rect2;
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};

    sfText_setPosition(my_paint->window.popup_size.popup_text, text_position);
    text_rect2 = sfText_getLocalBounds(my_paint->window.popup_size.popup_expl);
    sfText_setOrigin(my_paint->window.popup_size.popup_expl,
    (sfVector2f){text_rect2.width / 2.0f, text_rect2.height / 2.0f});
    text_position2 = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect2.width + 320) / 2 - text_rect2.left, text_position.y -
    text_rect2.height - 10};
    sfText_setPosition(my_paint->window.popup_size.popup_expl, text_position2);
}

static void update_popup_position(my_paint_t *my_paint,
    sfVector2u window_size)
{
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};
    sfFloatRect text_rect;
    sfVector2f text_position;

    sfRectangleShape_setSize(my_paint->window.popup_size.popup, popup_size);
    sfRectangleShape_setPosition(my_paint->window.popup_size.popup,
    popup_position);
    sfText_setCharacterSize(my_paint->window.popup_size.popup_text,
    popup_size.y * 0.1f);
    text_rect = sfText_getLocalBounds(my_paint->window.popup_size.popup_text);
    text_position = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect.width) / 2 - text_rect.left, popup_position.y + (popup_size.y
    - text_rect.height) / 2 - text_rect.top};
    update_popup2pos(my_paint, text_position, window_size, text_position);
}

static void draw_popup(my_paint_t *my_paint)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
    my_paint->window.popup_size.popup, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_size.popup_text, NULL);
        sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_size.popup_expl, NULL);
}

static void update_popup2open(my_paint_t *my_paint, sfVector2f text_position,
    sfVector2u window_size, sfVector2f text_position2)
{
    sfFloatRect text_rect2;
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};

    sfText_setPosition(my_paint->window.popup_open.popup_text, text_position);
    text_rect2 = sfText_getLocalBounds(my_paint->window.popup_open.popup_expl);
    sfText_setOrigin(my_paint->window.popup_open.popup_expl,
    (sfVector2f){text_rect2.width / 2.0f, text_rect2.height / 2.0f});
    text_position2 = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect2.width + 320) / 2 - text_rect2.left, text_position.y -
    text_rect2.height - 10};
    sfText_setPosition(my_paint->window.popup_open.popup_expl, text_position2);
}

static void update_popup_position_open(my_paint_t *my_paint,
    sfVector2u window_size)
{
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};
    sfFloatRect text_rect;
    sfVector2f text_position;

    sfRectangleShape_setSize(my_paint->window.popup_open.popup, popup_size);
    sfRectangleShape_setPosition(my_paint->window.popup_open.popup,
    popup_position);
    sfText_setCharacterSize(my_paint->window.popup_open.popup_text,
    popup_size.y * 0.1f);
    text_rect = sfText_getLocalBounds(my_paint->window.popup_open.popup_text);
    text_position = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect.width) / 2 - text_rect.left, popup_position.y + (popup_size.y
    - text_rect.height) / 2 - text_rect.top};
    update_popup2open(my_paint, text_position, window_size, text_position);
}

static void draw_popup_open(my_paint_t *my_paint)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
    my_paint->window.popup_open.popup, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_open.popup_text, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_open.popup_expl, NULL);
}

static void update_popup2save(my_paint_t *my_paint, sfVector2f text_position,
    sfVector2u window_size, sfVector2f text_position2)
{
    sfFloatRect text_rect2;
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};

    sfText_setPosition(my_paint->window.popup_save.popup_text, text_position);
    text_rect2 = sfText_getLocalBounds(my_paint->window.popup_save.popup_expl);
    sfText_setOrigin(my_paint->window.popup_save.popup_expl,
    (sfVector2f){text_rect2.width / 2.0f, text_rect2.height / 2.0f});
    text_position2 = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect2.width + 320) / 2 - text_rect2.left, text_position.y -
    text_rect2.height - 10};
    sfText_setPosition(my_paint->window.popup_save.popup_expl, text_position2);
}

static void update_popup_position_save(my_paint_t *my_paint,
    sfVector2u window_size)
{
    sfVector2f popup_size = {window_size.x * 0.3f, window_size.y * 0.3f};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};
    sfFloatRect text_rect;
    sfVector2f text_position;

    sfRectangleShape_setSize(my_paint->window.popup_save.popup, popup_size);
    sfRectangleShape_setPosition(my_paint->window.popup_save.popup,
    popup_position);
    sfText_setCharacterSize(my_paint->window.popup_save.popup_text,
    popup_size.y * 0.1f);
    text_rect = sfText_getLocalBounds(my_paint->window.popup_save.popup_text);
    text_position = (sfVector2f){popup_position.x + (popup_size.x -
    text_rect.width) / 2 - text_rect.left, popup_position.y + (popup_size.y
    - text_rect.height) / 2 - text_rect.top};
    update_popup2save(my_paint, text_position, window_size, text_position);
}

static void draw_popup_save(my_paint_t *my_paint)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
    my_paint->window.popup_save.popup, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_save.popup_text, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_save.popup_expl, NULL);
}

void display_popup(my_paint_t *my_paint)
{
    sfVector2u window_size = sfRenderWindow_getSize(WINDOW);

    if (my_paint->window.popup_size.display_popup != 0) {
        update_popup_position(my_paint, window_size);
        draw_popup(my_paint);
    }
    if (my_paint->window.popup_open.display_popup != 0) {
        update_popup_position_open(my_paint, window_size);
        draw_popup_open(my_paint);
    }
    if (my_paint->window.popup_save.display_popup != 0) {
        update_popup_position_save(my_paint, window_size);
        draw_popup_save(my_paint);
    }
    display_help(my_paint);
    display_about(my_paint);
}
