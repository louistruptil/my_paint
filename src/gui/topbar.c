/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** topbar.c
*/

#include "my_paint.h"

static void open_file(my_paint_t *my_paint, button_t *button)
{
    if (my_paint->window.popup_open.display_popup == 0)
        my_paint->window.popup_open.display_popup = 1;
    else
        my_paint->window.popup_open.display_popup = 0;
}

static void new_file(my_paint_t *my_paint, button_t *button)
{
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 0;
    }
}

static void hover_action(button_t *button)
{
    (void)button;
}

static void btn_file_two(my_paint_t *my_paint)
{
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {100, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "open file",
        sfColor_fromRGB(255, 255, 255),
    }, open_file, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {100, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "save file",
        sfColor_fromRGB(255, 255, 255),
    }, save_canva, hover_action);
}

void btn_file(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[0] = create_dropdown((button_options_t){
        {100, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "file",
        sfColor_fromRGB(255, 255, 255),
    });
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {100, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "new file",
        sfColor_fromRGB(255, 255, 255),
    }, new_file, hover_action);
    btn_file_two(my_paint);
}

static void btnrot(my_paint_t *my_paint)
{
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "rotate",
    }, rotate_selection, hover_action);
}

void btn_edition_two(my_paint_t *my_paint)
{
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
    {200, 8},
    {70, 20},
    sfColor_fromRGB(85, 98, 120),
    "cut",
    }, tool_cut, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "copy",
    }, tool_copy, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "paste",
    }, tool_paste, hover_action);
    btnrot(my_paint);
}

void btn_edition(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[1] = create_dropdown((button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "edition",
    });
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "pencil",
    }, tool_eq_pen, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "eraser",
    }, tool_eq_eraser, hover_action);
    btn_edition_two(my_paint);
}

void btn_help(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[2] = create_dropdown((button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "help"
    });
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "about"
    }, about_btn_act, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "help"
    }, help_btn_act, hover_action);
}
