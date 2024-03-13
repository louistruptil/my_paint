/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void rect_act(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 3;
}

void btn_recta(my_paint_t *my_paint)
{
    my_paint->gui.button[9] = create_button((button_options_t) {
        {20, 505},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/rectangle.png"
    }, rect_act, NULL);
}

static void draw_rectangle2(my_paint_t *my_paint, sfVector2i start_point,
    sfVector2i end_point)
{
    int left = MIN(start_point.x, end_point.x);
    int right = MAX(start_point.x, end_point.x);
    int top = MIN(start_point.y, end_point.y);
    int bottom = MAX(start_point.y, end_point.y);

    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x)
            update_pixel(my_paint, x, y);
    }
}

void draw_rectangle(my_paint_t *my_paint, sfEvent event,
    sfRenderWindow* window)
{
    static sfVector2i start_point;
    static sfVector2i end_point;
    static sfBool is_first_click = sfTrue;
    sfVector2i pixel_pos;

    if (event.type == sfEvtMouseButtonPressed) {
        pixel_pos.x = event.mouseButton.x;
        pixel_pos.y = event.mouseButton.y;
        if (is_first_click) {
            start_point = my_paint->canva.curr_mouse_pos;
            is_first_click = sfFalse;
        } else {
            end_point = my_paint->canva.curr_mouse_pos;
            is_first_click = sfTrue;
            draw_rectangle2(my_paint, start_point, end_point);
            start_point = (sfVector2i){0, 0};
            end_point = (sfVector2i){0, 0};
        }
    }
}
