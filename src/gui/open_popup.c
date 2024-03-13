/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** popup.c
*/

#include "my_paint.h"

void my_cpy(sfUint8 *dest, const sfUint8 *src, int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

static sfSprite *create_sprite(sfImage *image)
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2u image_size;
    sfVector2f scale;

    texture = sfTexture_createFromImage(image, NULL);
    sprite = sfSprite_create();
    image_size = sfImage_getSize(image);
    scale.x = 1920.0f / image_size.x;
    scale.y = 1080.0f / image_size.y;
    sfSprite_setScale(sprite, scale);
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

static int cpy_tab(my_paint_t *my_paint, sfRenderTexture *render_texture,
    sfSprite *sprite)
{
    sfImage *resized_image = sfTexture_copyToImage
    (sfRenderTexture_getTexture(render_texture));
    const sfUint8 *pixels = sfImage_getPixelsPtr(resized_image);

    my_cpy(my_paint->canva.canva_pixels, pixels, 1920 * 1080 * 4);
    my_paint->window.popup_open.popup_text_str[0] = '\0';
    my_paint->window.popup_open.display_popup = 0;
    sfImage_destroy(resized_image);
    sfRenderTexture_destroy(render_texture);
    sfSprite_destroy(sprite);
}

static int open_files(my_paint_t *my_paint, sfEvent event)
{
    sfImage *image = sfImage_createFromFile
    (my_paint->window.popup_open.popup_text_str);
    sfSprite *sprite;
    sfRenderTexture *render_texture;

    if (!image)
        return 0;
    sprite = create_sprite(image);
    render_texture = sfRenderTexture_create(1920, 1080, sfFalse);
    sfRenderTexture_drawSprite(render_texture, sprite, NULL);
    sfRenderTexture_display(render_texture);
    sfImage_destroy(image);
    cpy_tab(my_paint, render_texture, sprite);
}

void write_for_popupopen(my_paint_t *my_paint, sfEvent event)
{
    size_t len = 0;

    if (event.type == sfEvtTextEntered) {
        len = my_strlen(my_paint->window.popup_open.popup_text_str);
        if (event.text.unicode == '\b' && len > 0)
            my_paint->window.popup_open.popup_text_str[len - 1] = '\0';
        if (my_isdigit(event.text.unicode) || my_isalpha(event.text.unicode)
        || event.text.unicode == '.') {
            my_paint->window.popup_open.popup_text_str[len] =
            event.text.unicode;
            my_paint->window.popup_open.popup_text_str[len + 1] = '\0';
        }
        sfText_setString(my_paint->window.popup_open.popup_text,
            my_paint->window.popup_open.popup_text_str);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
        if (open_files(my_paint, event) == 1)
            return;
    }
}

static sfRectangleShape *create_popup_rectangle(sfVector2f size,
    sfVector2f position, sfColor color)
{
    sfRectangleShape *popup = sfRectangleShape_create();

    sfRectangleShape_setSize(popup, size);
    sfRectangleShape_setPosition(popup, position);
    sfRectangleShape_setFillColor(popup, color);
    return popup;
}

static sfText *create_popup_text(sfVector2f position, sfFont *font,
    unsigned int characterSize, sfColor color)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, characterSize);
    sfText_setColor(text, color);
    sfText_setPosition(text, position);
    return text;
}

static void initialize_popup(my_paint_t *my_paint)
{
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f popup_size = {300, 200};
    sfVector2f popup_position = {window_size.x / 2.0f - popup_size.x / 2.0f,
        window_size.y / 2.0f - popup_size.y / 2.0f};
    sfColor color = sfColor_fromRGB(85, 98, 120);
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfVector2f text_position = {popup_position.x + (popup_size.x - 200) / 2,
        popup_position.y + (popup_size.y - 24) / 2};

    my_paint->window.popup_open.popup = create_popup_rectangle(popup_size,
                                                    popup_position, color);
    my_paint->window.popup_open.popup_text = create_popup_text(text_position,
    font, 24, sfWhite);
}

static void cleanup_popup(my_paint_t *my_paint)
{
    sfRectangleShape_destroy(my_paint->window.popup_open.popup);
    sfText_destroy(my_paint->window.popup_open.popup_text);
    free(my_paint->window.popup_open.popup_text_str);
}

int create_popup_open(my_paint_t *my_paint)
{
    my_paint->window.popup_open.display_popup = 0;
    initialize_popup(my_paint);
    sfText_setString(my_paint->window.popup_open.popup_text, "");
    my_paint->window.popup_open.popup_text_str = malloc(sizeof(char) * 100);
    if (my_paint->window.popup_open.popup_text_str == NULL) {
        cleanup_popup(my_paint);
        return 0;
    }
    my_paint->window.popup_open.popup_text_str[0] = '\0';
    return 1;
}
