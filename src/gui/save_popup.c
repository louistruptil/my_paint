/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** popup.c
*/

#include "my_paint.h"

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
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f popupSize = {300, 200};
    sfVector2f popupPosition = {windowSize.x / 2.0f - popupSize.x / 2.0f,
        windowSize.y / 2.0f - popupSize.y / 2.0f};
    sfColor color = sfColor_fromRGB(85, 98, 120);
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfVector2f textPosition = {popupPosition.x + (popupSize.x - 200) / 2,
        popupPosition.y + (popupSize.y - 24) / 2};

    my_paint->window.popup_save.popup = create_popup_rectangle(popupSize,
                                                    popupPosition, color);
    my_paint->window.popup_save.popup_text = create_popup_text(textPosition,
    font, 24, sfWhite);
}

static void cleanup_popup(my_paint_t *my_paint)
{
    sfRectangleShape_destroy(my_paint->window.popup_save.popup);
    sfText_destroy(my_paint->window.popup_save.popup_text);
    free(my_paint->window.popup_save.popup_text_str);
}

int create_popup_save(my_paint_t *my_paint)
{
    my_paint->window.popup_save.display_popup = 0;
    initialize_popup(my_paint);
    sfText_setString(my_paint->window.popup_save.popup_text, "");
    my_paint->window.popup_save.popup_text_str = malloc(sizeof(char) * 100);
    if (my_paint->window.popup_save.popup_text_str == NULL) {
        cleanup_popup(my_paint);
        return 0;
    }
    my_paint->window.popup_save.popup_text_str[0] = '\0';
    return 1;
}

int save_files(my_paint_t *my_paint, sfEvent event)
{
    sfImage *image = sfTexture_copyToImage(my_paint->canva.canva_texture);

    sfImage_saveToFile(image, my_paint->window.popup_save.popup_text_str);
    sfImage_destroy(image);
    my_paint->window.popup_save.popup_text_str[0] = '\0';
    my_paint->window.popup_save.display_popup = 0;
    return 0;
}

void write_for_popupsave(my_paint_t *my_paint, sfEvent event)
{
    size_t len = 0;

    if (event.type == sfEvtTextEntered) {
        len = my_strlen(my_paint->window.popup_save.popup_text_str);
        if (event.text.unicode == '\b' && len > 0)
            my_paint->window.popup_save.popup_text_str[len - 1] = '\0';
        if (my_isdigit(event.text.unicode) || my_isalpha(event.text.unicode)
        || event.text.unicode == '.') {
            my_paint->window.popup_save.popup_text_str[len] =
            event.text.unicode;
            my_paint->window.popup_save.popup_text_str[len + 1] = '\0';
        }
        sfText_setString(my_paint->window.popup_save.popup_text,
            my_paint->window.popup_save.popup_text_str);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
        if (save_files(my_paint, event) == 1)
            return;
    }
}
