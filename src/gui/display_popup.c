/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include <stdio.h>
#include "my_paint.h"

static void update_popup_position(my_paint_t *my_paint, sfVector2u windowSize)
{
    sfVector2f popupSize = {windowSize.x * 0.3f, windowSize.y * 0.3f};
    sfVector2f popupPosition = {windowSize.x / 2.0f - popupSize.x / 2.0f,
        windowSize.y / 2.0f - popupSize.y / 2.0f};
    sfFloatRect textRect;
    sfVector2f textPosition;

    sfRectangleShape_setSize(my_paint->window.popup_size.popup, popupSize);
    sfRectangleShape_setPosition(my_paint->window.popup_size.popup,
    popupPosition);
    sfText_setCharacterSize(my_paint->window.popup_size.popup_text,
        popupSize.y * 0.1f);
    textRect = sfText_getLocalBounds(my_paint->window.popup_size.popup_text);
    textPosition = (sfVector2f){popupPosition.x +
        (popupSize.x - textRect.width) / 2 - textRect.left, popupPosition.y
        + (popupSize.y - textRect.height) / 2 - textRect.top};
    sfText_setPosition(my_paint->window.popup_size.popup_text, textPosition);
}

static void draw_popup(my_paint_t *my_paint)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
    my_paint->window.popup_size.popup, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_size.popup_text, NULL);
}

static void update_popup_position_open(my_paint_t *my_paint,
    sfVector2u windowSize)
{
    sfVector2f popupSize = {windowSize.x * 0.3f, windowSize.y * 0.3f};
    sfVector2f popupPosition = {windowSize.x / 2.0f - popupSize.x / 2.0f,
        windowSize.y / 2.0f - popupSize.y / 2.0f};
    sfFloatRect textRect;
    sfVector2f textPosition;

    sfRectangleShape_setSize(my_paint->window.popup_open.popup, popupSize);
    sfRectangleShape_setPosition(my_paint->window.popup_open.popup,
    popupPosition);
    sfText_setCharacterSize(my_paint->window.popup_open.popup_text,
        popupSize.y * 0.1f);
    textRect = sfText_getLocalBounds(my_paint->window.popup_open.popup_text);
    textPosition = (sfVector2f){popupPosition.x +
        (popupSize.x - textRect.width) / 2 - textRect.left, popupPosition.y
        + (popupSize.y - textRect.height) / 2 - textRect.top};
    sfText_setPosition(my_paint->window.popup_open.popup_text, textPosition);
}

static void draw_popup_open(my_paint_t *my_paint)
{
    sfRenderWindow_drawRectangleShape(WINDOW,
    my_paint->window.popup_open.popup, NULL);
    sfRenderWindow_drawText(WINDOW,
    my_paint->window.popup_open.popup_text, NULL);
}

void display_popup(my_paint_t *my_paint)
{
    sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);

    if (my_paint->window.popup_size.display_popup != 0) {
        update_popup_position(my_paint, windowSize);
        draw_popup(my_paint);
    }
    if (my_paint->window.popup_open.display_popup != 0) {
        update_popup_position_open(my_paint, windowSize);
        draw_popup_open(my_paint);
    }
}
