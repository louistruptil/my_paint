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

static void tool_eq_picker(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 2;
}

static void tool_eq_bucket(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 3;
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

static void btn_edition(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[1] = create_dropdown((button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "edition",
        sfColor_fromRGB(255, 255, 255),
    });
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "pencil",
        sfColor_fromRGB(255, 255, 255),
    }, tool_eq_pen, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[1], (button_options_t){
        {200, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "eraser",
        sfColor_fromRGB(255, 255, 255),
    }, tool_eq_eraser, hover_action);
}

static void btn_help(my_paint_t *my_paint)
{
    my_paint->gui.dropdown[2] = create_dropdown((button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "help",
        sfColor_fromRGB(255, 255, 255)
    });
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "about",
        sfColor_fromRGB(255, 255, 255)
    }, new_file, hover_action);
    add_item_to_dropdown(my_paint->gui.dropdown[2], (button_options_t){
        {300, 8},
        {70, 20},
        sfColor_fromRGB(85, 98, 120),
        "help",
        sfColor_fromRGB(255, 255, 255)
    }, open_file, hover_action);
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

static void btn_pen(my_paint_t *my_paint)
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
    add_item_to_dropdown(my_paint->gui.dropdown[3], (button_options_t){
        {75, 20},
        {50, 50},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/circle.png"
    }, set_circle, hover_action);
}

static void btn_eraser(my_paint_t *my_paint)
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

static void btn_size(my_paint_t *my_paint)
{
    my_paint->gui.button[1] = create_button((button_options_t) {
        {11, 920},
        {50, 50},
        sfColor_fromRGB(85, 98, 120),
        "SIZE",
        sfColor_fromRGB(255, 255, 255),
    }, set_size, hover_action);
}

static void btn_picker(my_paint_t *my_paint)
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

static void btn_bucket(my_paint_t *my_paint)
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

static int create_interface_buttons(my_paint_t *my_paint)
{
    btn_file(my_paint);
    btn_edition(my_paint);
    btn_help(my_paint);
    btn_pen(my_paint);
    btn_eraser(my_paint);
    btn_size(my_paint);
    btn_picker(my_paint);
    btn_bucket(my_paint);
}

static int create_popup(my_paint_t *my_paint)
{
    my_paint->window.display_popup = 0;
    my_paint->window.popup = sfRectangleShape_create();
    sfVector2f popupSize = {300, 200};
    sfRectangleShape_setSize(my_paint->window.popup, popupSize);
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f popupPosition = {windowSize.x / 2.0f - popupSize.x / 2.0f, windowSize.y / 2.0f - popupSize.y / 2.0f};
    sfRectangleShape_setPosition(my_paint->window.popup, popupPosition);
    sfColor color = sfColor_fromRGB(85, 98, 120);
    sfRectangleShape_setFillColor(my_paint->window.popup, color);
    my_paint->window.popup_text = sfText_create();
    sfFloatRect textRect = sfText_getLocalBounds(my_paint->window.popup_text);
    sfVector2f textPosition = {
        popupPosition.x + (popupSize.x - textRect.width) / 2 - textRect.left,
        popupPosition.y + (popupSize.y - textRect.height) / 2 - textRect.top
    };
    sfText_setPosition(my_paint->window.popup_text, textPosition);
    sfText_setCharacterSize(my_paint->window.popup_text, 24);
    sfText_setColor(my_paint->window.popup_text, sfWhite);
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfText_setFont(my_paint->window.popup_text, font);
    my_paint->window.popup_text_str = malloc(sizeof(char) * 100);
    my_paint->window.popup_text_str[0] = '\0';
    sfText_setString(my_paint->window.popup_text, "");
}

int create_interface(my_paint_t *my_paint)
{
    my_paint->interface.left_bar = sfRectangleShape_create();
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfRectangleShape_setSize(my_paint->interface.left_bar, (sfVector2f){75, windowSize.y});
    sfColor sf = {3, 6, 48, 255};
    sfRectangleShape_setFillColor(my_paint->interface.left_bar, sf);
    sfVector2f position = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.left_bar, position);
    my_paint->interface.top_bar = sfRectangleShape_create();
    sfRectangleShape_setSize(my_paint->interface.top_bar, (sfVector2f){windowSize.x, 35});
    sfColor sf2 = {3, 6, 48, 255};
    sfRectangleShape_setFillColor(my_paint->interface.top_bar, sf2);
    sfVector2f position2 = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.top_bar, position2);
    create_interface_buttons(my_paint);
    create_popup(my_paint);
}