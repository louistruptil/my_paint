/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** button.c
*/

#include <stdio.h>
#include "my_paint.h"

static bool create_text_button(button_options_t options, button_t *button)
{
    sfFloatRect text_rect;
    float text_x;
    float text_y;

    button->font = sfFont_createFromFile("assets/font.ttf");
    CHECK_NULL(button->font, false);
    button->text = sfText_create();
    sfText_setString(button->text, options.text);
    sfText_setFont(button->text, button->font);
    sfText_setFillColor(button->text, options.text_color.r ?
        options.text_color : sfWhite);
    sfText_setCharacterSize(button->text, options.size.y / 2);
    text_rect = sfText_getLocalBounds(button->text);
    text_x = options.pos.x + (options.size.x - text_rect.width) / 2;
    text_y = options.pos.y + (options.size.y - text_rect.height) / 3;
    sfText_setPosition(button->text, (sfVector2f){text_x, text_y});
    button->img_texture = NULL;
    return true;
}

static bool create_img_button(button_options_t options, button_t *button)
{
    button->img_texture = sfTexture_createFromFile(options.img, NULL);
    CHECK_NULL(button->img_texture, false);
    sfRectangleShape_setTexture(button->rect, button->img_texture,
        sfTrue);
    button->text = NULL;
    button->font = NULL;
    return true;
}

static void create_btn_set_value(button_options_t options,
    void(*hover)(button_t *), button_t *button)
{
    button->hover = hover;
    button->options = options;
    button->state = NONE;
}

button_t *create_button(button_options_t options,
    void (*action)(my_paint_t *, button_t *), void (*hover)(button_t *))
{
    button_t *button = malloc(sizeof(button_t));

    CHECK_NULL(button, NULL);
    button->rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(button->rect, options.pos);
    sfRectangleShape_setSize(button->rect, options.size);
    if (options.color.a != 0)
        sfRectangleShape_setFillColor(button->rect, options.color);
    button->is_clicked = is_button_clicked;
    button->is_hover = is_button_hover;
    button->action = action;
    create_btn_set_value(options, hover, button);
    if (options.text)
        if (!create_text_button(options, button))
            return NULL;
    if (options.img)
        if (!create_img_button(options, button))
            return NULL;
    return button;
}

bool is_button_clicked(button_t *button, sfMouseButtonEvent *event)
{
    sfFloatRect rect;
    bool is_clicked;

    if (button == NULL || event == NULL || button->rect == NULL ||
        button->state == NONE)
        return false;
    rect = sfRectangleShape_getGlobalBounds(button->rect);
    is_clicked = sfFloatRect_contains(&rect, event->x, event->y);
    if (is_clicked && event->type == sfEvtMouseButtonPressed) {
        button->state = PRESSED;
        return true;
    }
    button->state = NONE;
    return false;
}

bool is_button_hover(button_t *button, sfMouseMoveEvent *event)
{
    sfFloatRect rect;
    sfBool is_hover;

    if (button == NULL || event == NULL || button->rect == NULL ||
        event->type != sfEvtMouseMoved)
        return false;
    rect = sfRectangleShape_getGlobalBounds(button->rect);
    is_hover = sfFloatRect_contains(&rect, event->x, event->y);
    if (is_hover && button->state != PRESSED) {
        button->state = HOVER;
        if (button->hover)
            button->hover(button);
    } else
        button->state = button->state == PRESSED ? PRESSED : NONE;
    return is_hover ? true : false;
}

void render_button(my_paint_t *my_paint, button_t *button)
{
    sfVector2f scale;
    sfVector2f buttonSize;
    sfVector2f btn_pos;
    sfFloatRect textRect;
    sfVector2f textPos;

    calculate_window_scale(my_paint, &scale);
    update_button_size(button->rect, &buttonSize, scale, button->options.size);
    update_button_position(button->rect, &btn_pos, scale, button->options.pos);
    sfRenderWindow_drawRectangleShape(WINDOW, button->rect, NULL);
    if (button->options.text && button->text && button->font) {
        textRect = sfText_getLocalBounds(button->text);
        sfText_setCharacterSize(button->text, 16 * scale.y);
        textPos = (sfVector2f){
            btn_pos.x + (buttonSize.x - textRect.width) / 2 - textRect.left,
            btn_pos.y + (buttonSize.y - textRect.height) / 2 - textRect.top
        };
        sfText_setPosition(button->text, textPos);
        sfRenderWindow_drawText(WINDOW, button->text, NULL);
    }
}

static void handle_button_state(my_paint_t *my_paint, button_t *button)
{
    if (my_paint == NULL || button == NULL)
        return;
    if (button->state == HOVER || button->state == PRESSED ||
        button->state == RELEASED) {
        my_paint->can_draw = false;
    }
    if (button->state && button->state == HOVER) {
        if (button->hover)
            button->hover(button);
        sfRectangleShape_setOutlineThickness(button->rect, 2);
    } else {
        if (button->options.color.a != 0)
            sfRectangleShape_setFillColor(button->rect, button->options.color);
        sfRectangleShape_setOutlineThickness(button->rect, 0);
        sfRectangleShape_setOutlineColor(button->rect, sfWhite);
    }
}

void display_button(my_paint_t *my_paint, button_t *button)
{
    render_button(my_paint, button);
    handle_button_state(my_paint, button);
}
