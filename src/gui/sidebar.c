/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** sidebar.c
*/

#include "my_paint.h"

static void hover_action(button_t *button)
{
    (void)button;
}

static int set_square(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 1;
}

static int set_circle(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 0;
}

static int set_size(my_paint_t *my_paint)
{
    if (my_paint->window.display_popup == 0)
        my_paint->window.display_popup = 1;
    else
        my_paint->window.display_popup = 0;
}

static void btn_pen_two(my_paint_t *my_paint)
{
    add_item_to_dropdown(my_paint->gui.dropdown[3], (button_options_t){
        {75, 20},
        {50, 50},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/circle.png"
    }, set_circle, hover_action);
}

void btn_pen(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[3] = create_dropdown((button_options_t){
        {22, 65},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/pen.png"
    });
    add_item_to_dropdown(my_paint->gui.dropdown[3], (button_options_t){
        {75, 20},
        {50, 50},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/square.png"
    }, set_square, hover_action);
    btn_pen_two(my_paint);
}

void btn_eraser(my_paint_t *my_paint)
{
    my_paint->gui.button[0] = create_button((button_options_t) {
        {20, 120},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/eraser.png"
    }, tool_eq_eraser, hover_action);
}

void btn_size(my_paint_t *my_paint)
{
    my_paint->gui.button[1] = create_button((button_options_t) {
        {11, 920},
        {50, 50},
        sfColor_fromRGB(85, 98, 120),
        "SIZE",
        sfColor_fromRGB(255, 255, 255),
    }, set_size, hover_action);
}

void btn_picker(my_paint_t *my_paint)
{
    my_paint->gui.button[2] = create_button((button_options_t) {
        {20, 175},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/color_picker.png"
    }, tool_eq_picker, hover_action);
}

void btn_bucket(my_paint_t *my_paint)
{
    my_paint->gui.button[3] = create_button((button_options_t) {
        {20, 230},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/bucket.png"
    }, tool_eq_bucket, hover_action);
}
