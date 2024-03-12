/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

static int draw_cmd(my_paint_t *my_paint, sfEvent event)
{
    drawing_loop(my_paint, event);
}

static int ereased_cmd(my_paint_t *my_paint, sfEvent event)
{
    drawing_loop(my_paint, event);
}

static void select_color_on_selector_two(my_paint_t *my_paint,
    sfVector2i mousePos, sfColor color)
{
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        color = sfImage_getPixel(my_paint->gui.color_selector.image,
            mousePos.x, mousePos.y);
        my_paint->tools.rgba[0] = color.r;
        my_paint->tools.rgba[1] = color.g;
        my_paint->tools.rgba[2] = color.b;
        my_paint->tools.rgba[3] = color.a;
    }
    sfRectangleShape_setFillColor(my_paint->gui.color_selector.selected_color,
    sfColor_fromRGBA(my_paint->tools.rgba[0], my_paint->tools.rgba[1],
    my_paint->tools.rgba[2], my_paint->tools.rgba[3]));
}

static void select_color_on_selector(my_paint_t *my_paint, sfEvent event)
{
    sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);
    sfVector2f selectorPos = {(float)(windowSize.x - 355), 45};
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(WINDOW);
    sfColor color;

    sfRectangleShape_setPosition(my_paint->gui.color_selector.rect,
        selectorPos);
    if (mousePos.x < windowSize.x - 355 || mousePos.x > windowSize.x - 55)
        return;
    mousePos.x = (mousePos.x - (windowSize.x - 355)) * 1000 / 300;
    mousePos.y = (mousePos.y - 45) * 981 / 300;
    if (mousePos.x < 0 || mousePos.x > 1920 || mousePos.y < 0 ||
        mousePos.y > 1080)
        return;
    select_color_on_selector_two(my_paint, mousePos, color);
}

void do_select_action(my_paint_t *my_paint, sfEvent event)
{
    if (!my_paint->can_draw)
        return;
    if (my_paint->tools.color_selector) {
        select_color_on_selector(my_paint, event);
        return;
    }
    if (my_paint->tools.actual_tools == 0)
        draw_cmd(my_paint, event);
    if (my_paint->tools.actual_tools == 1)
        ereased_cmd(my_paint, event);
    if (my_paint->tools.actual_tools == 2)
        color_picker(my_paint, event);
    if (my_paint->tools.actual_tools == 3)
        color_bucket(my_paint, event);
}

void write_for_popup(my_paint_t *my_paint, sfEvent event)
{
    size_t len = 0;

    if (event.type == sfEvtTextEntered) {
        len = my_strlen(my_paint->window.popup_size.popup_text_str);
        if (event.text.unicode == '\b' && len > 0)
            my_paint->window.popup_size.popup_text_str[len - 1] = '\0';
        if (len < 2 && my_isdigit(event.text.unicode)) {
            my_paint->window.popup_size.popup_text_str[len] =
            event.text.unicode;
            my_paint->window.popup_size.popup_text_str[len + 1] = '\0';
        }
        sfText_setString(my_paint->window.popup_size.popup_text,
            my_paint->window.popup_size.popup_text_str);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
        my_paint->tools.size =
        atoi(my_paint->window.popup_size.popup_text_str);
        my_paint->window.popup_size.popup_text_str[0] = '\0';
        my_paint->window.popup_size.display_popup = 0;
    }
}
