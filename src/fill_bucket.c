/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** fill_bucket.c
*/

#include <stdio.h>
#include "my_paint.h"

static void push(sfVector2i pixel, sfVector2i *stack, int *stack_top)
{
    stack[*stack_top] = pixel;
    (*stack_top)++;
}

static int is_within_bounds(const int x, const int y)
{
    return (x >= 0 && x < CANVA_WIDTH && y >= 0 && y < CANVA_HEIGHT);
}

static int is_same_color(my_paint_t *my_paint, int x, int y, sfColor old_color)
{
    return sfColor_toInteger(get_pixel_color(my_paint, x, y))
    == sfColor_toInteger(old_color);
}

void push_neighbors(int *stack_top, sfVector2i *stack, sfVector2i current)
{
    push((sfVector2i){current.x + 1, current.y}, stack, stack_top);
    push((sfVector2i){current.x - 1, current.y}, stack, stack_top);
    push((sfVector2i){current.x, current.y + 1}, stack, stack_top);
    push((sfVector2i){current.x, current.y - 1}, stack, stack_top);
}

void flood_fill(my_paint_t *my_paint, int x, int y, sfColor new_color)
{
    const sfColor old_color = get_pixel_color(my_paint, x, y);
    const int stack_size = CANVA_WIDTH * CANVA_HEIGHT * 4;
    int stack_top = 0;
    sfVector2i *stack;
    sfVector2i current;

    if (sfColor_toInteger(old_color) == sfColor_toInteger(new_color))
        return;
    stack = malloc(sizeof(sfVector2i) * stack_size);
    push((sfVector2i){x, y}, stack, &stack_top);
    while (stack_top > 0) {
        stack_top--;
        current = stack[stack_top];
        if (!is_within_bounds(current.x, current.y) ||
            !is_same_color(my_paint, current.x, current.y, old_color))
            continue;
        set_pixel_color(my_paint, current.x, current.y, new_color);
        push_neighbors(&stack_top, stack, current);
    }
    free(stack);
}

void color_bucket(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i mouse_pos;
    sfVector2u window_size;
    sfVector2f scale;
    int scaled_mouse_x;
    int scaled_mouse_y;

    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        mouse_pos = sfMouse_getPositionRenderWindow(my_paint->window.window);
        window_size = sfRenderWindow_getSize(my_paint->window.window);
        scale.x = 1920.0f / window_size.x;
        scale.y = 1080.0f / window_size.y;
        scaled_mouse_x = mouse_pos.x * scale.x;
        scaled_mouse_y = mouse_pos.y * scale.y;
        flood_fill(my_paint, scaled_mouse_x, scaled_mouse_y,
            sfColor_fromRGBA(my_paint->tools.rgba[0],
            my_paint->tools.rgba[1],
            my_paint->tools.rgba[2],
            my_paint->tools.rgba[3]));
    }
}
