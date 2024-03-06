/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/
#include "my_paint.h"

static void open_file(my_paint_t *my_paint, button_t *button)
{
    my_putstr("Open files\n");
}

static void new_file(my_paint_t *my_paint, button_t *button)
{
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 255;
    }
}

int save_canva(my_paint_t *my_paint, sfEvent event)
{
    sfImage *image = sfTexture_copyToImage(my_paint->canva.canva_texture);
    sfImage_saveToFile(image, "canva.jpg");
    sfImage_destroy(image);
    return 0;
}

static void hover_action(button_t *button)
{
    printf("hover\n");
}

static void tool_eq_pen(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 0;
}

static void tool_eq_eraser(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 1;
}

void handle_resize_interface(my_paint_t *my_paint, sfEvent event)
{
    if (event.type == sfEvtResized) {
        sfVector2u windowSize = {event.size.width, event.size.height};
        sfRectangleShape_setSize(my_paint->interface.left_bar, (sfVector2f){50, windowSize.y});
        sfVector2f position = {0, 0};
        sfRectangleShape_setPosition(my_paint->interface.left_bar, position);

        sfRectangleShape_setSize(my_paint->interface.top_bar, (sfVector2f){windowSize.x, 35});
        sfRectangleShape_setPosition(my_paint->interface.top_bar, position);
    }
}

static void btn_file(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[0] = create_dropdown((button_options_t){
        {51, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "file"
    });
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {51, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "new file"
    }, new_file, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {51, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "open file"
    }, open_file, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[0], (button_options_t){
        {51, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "save file"
    }, save_canva, hover_action);
}

static void btn_edition(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[1] = create_dropdown((button_options_t){
        {150, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "edition"
    });
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {150, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "pencil"
    }, tool_eq_pen, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {150, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "eraser"
    }, tool_eq_eraser, hover_action);
}

static void btn_help(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[2] = create_dropdown((button_options_t){
        {250, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "help"
    });
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {250, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "about"
    }, new_file, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {250, 8},
        {70, 20},
        sfColor_fromRGB(0, 0, 0),
        "help"
    }, open_file, hover_action);
}

static int create_interface_buttons(my_paint_t *my_paint)
{
    btn_file(my_paint);
    btn_edition(my_paint);
    btn_help(my_paint);
}

int create_interface(my_paint_t *my_paint)
{
    my_paint->interface.left_bar = sfRectangleShape_create();
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfRectangleShape_setSize(my_paint->interface.left_bar, (sfVector2f){50, windowSize.y});
    sfColor sf = {255, 0, 153, 255};
    sfRectangleShape_setFillColor(my_paint->interface.left_bar, sf);
    sfVector2f position = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.left_bar, position);
    my_paint->interface.top_bar = sfRectangleShape_create();
    sfRectangleShape_setSize(my_paint->interface.top_bar, (sfVector2f){windowSize.x, 35});
    sfColor sf2 = {255, 0, 153, 255};
    sfRectangleShape_setFillColor(my_paint->interface.top_bar, sf2);
    sfVector2f position2 = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.top_bar, position2);
    create_interface_buttons(my_paint);
}