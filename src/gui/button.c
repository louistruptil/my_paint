/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** button.c
*/

#include "my_paint.h"

static bool create_text_button(button_options_t options, button_t *button)
{
    sfFloatRect text_rect;
    float text_x;
    float text_y;

    button->font = sfFont_createFromFile("assets/font.ttf");
    if (!button->font)
        return false;
    button->text = sfText_create();
    sfText_setString(button->text, options.text);
    sfText_setFont(button->text, button->font);
    sfText_setCharacterSize(button->text, options.size.y / 2);
    text_rect = sfText_getLocalBounds(button->text);
    text_x = options.pos.x + (options.size.x - text_rect.width) / 2;
    text_y = options.pos.y + (options.size.y - text_rect.height) / 3;
    sfText_setPosition(button->text, (sfVector2f){text_x, text_y});
    return true;
}

button_t *create_button(button_options_t options, void (*action)(my_paint_t *))
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(button->rect, options.pos);
    sfRectangleShape_setSize(button->rect, options.size);
    sfRectangleShape_setFillColor(button->rect, options.color);
    button->is_clicked = is_button_clicked;
    button->is_hover = is_button_hover;
    button->action = action;
    if (options.text)
        if (!create_text_button(options, button))
            return NULL;
    if (options.img) {
    }
    return button;
}

bool is_button_clicked(button_t *button, sfMouseButtonEvent *event)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(button->rect);
    sfBool is_clicked = sfFloatRect_contains(&rect, event->x, event->y);

    if (is_clicked && event->type == sfEvtMouseButtonPressed) {
        button->state = PRESSED;
        return true;
    } else {
        button->state = NONE;
        return false;
    }
}

bool is_button_hover(button_t *button, sfMouseMoveEvent *event)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(button->rect);
    sfBool is_hover = sfFloatRect_contains(&rect, event->x, event->y);

    button->state = is_hover ? HOVER : NONE;
    return is_hover ? true : false;
}

void destroy_button(button_t *button)
{
    sfRectangleShape_destroy(button->rect);
    if (button->font) {
        sfFont_destroy(button->font);
        sfText_destroy(button->text);
    }
    free(button);
}

void display_button(sfRenderWindow *window, button_t *button)
{
    sfRenderWindow_drawRectangleShape(window, button->rect, NULL);
    if (button->font)
        sfRenderWindow_drawText(window, button->text, NULL);
}
