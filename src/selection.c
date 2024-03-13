/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** selection.c
*/

#include "my_paint.h"

void adjust_selection_coordinates(selection_t *selection,
    sfVector2u window_size)
{
    sfVector2f scale = {1920.0f / window_size.x, 1080.0f / window_size.y};

    selection->pos.x *= scale.x;
    selection->pos.y *= scale.y;
    selection->size.x *= scale.x;
    selection->size.y *= scale.y;
    if (selection->size.x < 0) {
        selection->pos.x += selection->size.x;
        selection->size.x = -selection->size.x;
    }
    if (selection->size.y < 0) {
        selection->pos.y += selection->size.y;
        selection->size.y = -selection->size.y;
    }
}

void delete_selection_from_canvas(my_paint_t *my_paint,
    selection_t select)
{
    int index;

    for (int y = select.pos.y; y < select.pos.y + select.size.y; y++) {
        for (int x = select.pos.x; x < select.pos.x + select.size.x; x++) {
            index = (x + y * 1920) * 4;
            my_paint->canva.canva_pixels[index] = 0;
            my_paint->canva.canva_pixels[index + 1] = 0;
            my_paint->canva.canva_pixels[index + 2] = 0;
            my_paint->canva.canva_pixels[index + 3] = 0;
        }
    }
}

static void delete_selection(my_paint_t *my_paint, sfEvent event)
{
    selection_t selection = my_paint->tools.selection;
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDelete) {
        adjust_selection_coordinates(&selection, window_size);
        delete_selection_from_canvas(my_paint, selection);
    }
}

static void selection_tool_part_two(my_paint_t *my_paint,
    sfEvent event, sfVector2i mousePos)
{
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        my_paint->tools.selection.size.x =
            mousePos.x - my_paint->tools.selection.pos.x;
        my_paint->tools.selection.size.y =
            mousePos.y - my_paint->tools.selection.pos.y;
    }
    if (event.type == sfEvtMouseButtonReleased)
        sfRectangleShape_setFillColor(my_paint->tools.selection.rect,
            sfColor_fromRGBA(25, 25, 50, 65));
    sfRectangleShape_setSize(my_paint->tools.selection.rect,
        my_paint->tools.selection.size);
    delete_selection(my_paint, event);
    copy_selection(my_paint, event);
}

void selection_tool(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(WINDOW);

    if (event.type == sfEvtMouseButtonPressed) {
        my_paint->tools.selection.pos = mousePos;
        sfRectangleShape_setSize(my_paint->tools.selection.rect,
            (sfVector2f){0, 0});
        sfRectangleShape_setPosition(my_paint->tools.selection.rect,
        (sfVector2f){my_paint->tools.selection.pos.x,
            my_paint->tools.selection.pos.y});
        sfRectangleShape_setFillColor(my_paint->tools.selection.rect,
            sfColor_fromRGBA(175, 175, 175, 100));
    }
    selection_tool_part_two(my_paint, event, mousePos);
}

static void tool_eq_selection(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 4;
}

bool init_selection_tool(my_paint_t *my_paint)
{
    my_paint->tools.selection.rect = sfRectangleShape_create();
    sfRectangleShape_setOutlineThickness(my_paint->tools.selection.rect,
    1);
    sfRectangleShape_setOutlineColor(my_paint->tools.selection.rect,
        sfColor_fromRGBA(175, 175, 175, 255));
    sfRectangleShape_setFillColor(my_paint->tools.selection.rect,
        sfColor_fromRGBA(175, 175, 175, 100));
    my_paint->gui.button[7] = create_button((button_options_t) {
        {20, 395},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/selection.png"
    }, tool_eq_selection, NULL);
    return true;
}
