/*
 * This file is part of the espChathan Project
 *
 * Copyright (C) 2026 Robin John <johnrobin044@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <esp_lcd_touch_xpt2046.h>
#include <microui.h>
#include <hagl_hal.h>
#include <hagl.h>
#include <font6x9.h>
#include <esp_lcd_touch.h>
#include <esp_log.h>
#include <hagl/bitmap.h>
#include <stdint.h>

#include "globals.h"
#include "config.h"
#include "hagl/rectangle.h"
#include "icons.h"
#include "render.h"
#include "layout.h"

#define TAG "UI"

hagl_backend_t *display;

mu_Context muCtx;

/* Set default theme to dark */
theme_state_t globalThemeState = DARK;

int
get_text_width(mu_Font font, const char *str, int len)
{
    if (len < 0)
    {
        len = strlen(str);
    }
    return len * FONT_WIDTH;
}

int
get_text_height(mu_Font font)
{
    return FONT_HEIGHT;
}

static mu_Color
color_to_mu(uint16_t rgb565)
{
    return (mu_Color) { .r = ((rgb565 >> 11) & 0x1F) << 3,
                        .g = ((rgb565 >> 5) & 0x3F) << 2,
                        .b = (rgb565 & 0x1F) << 3,
                        .a = 255 };
}

void
apply_theme()
{
    if (globalThemeState == DARK)
    {
        muCtx.style->colors[MU_COLOR_TEXT]        = color_to_mu(MILKY_WHITE);
        muCtx.style->colors[MU_COLOR_BORDER]      = color_to_mu(TAUPE_GRAY);
        muCtx.style->colors[MU_COLOR_WINDOWBG]    = color_to_mu(ESPRESSO_BLACK);
        muCtx.style->colors[MU_COLOR_TITLEBG]     = color_to_mu(CHARCOAL_BG);
        muCtx.style->colors[MU_COLOR_TITLETEXT]   = color_to_mu(MILKY_WHITE);
        muCtx.style->colors[MU_COLOR_PANELBG]     = color_to_mu(CHARCOAL_BG);
        muCtx.style->colors[MU_COLOR_BUTTON]      = color_to_mu(CHARCOAL_BG);
        muCtx.style->colors[MU_COLOR_BUTTONHOVER] = color_to_mu(CASHMERE_GRAY);
        muCtx.style->colors[MU_COLOR_BUTTONFOCUS] = color_to_mu(SLATE_BLUE);
        muCtx.style->colors[MU_COLOR_BASE]        = color_to_mu(CHARCOAL_BG);
        muCtx.style->colors[MU_COLOR_BASEHOVER]   = color_to_mu(CASHMERE_GRAY);
        muCtx.style->colors[MU_COLOR_BASEFOCUS]   = color_to_mu(SLATE_BLUE);
        muCtx.style->colors[MU_COLOR_SCROLLBASE]  = color_to_mu(ESPRESSO_BLACK);
        muCtx.style->colors[MU_COLOR_SCROLLTHUMB] = color_to_mu(TAUPE_GRAY);
    }
    else
    {
        muCtx.style->colors[MU_COLOR_TEXT]        = color_to_mu(ESPRESSO_BLACK);
        muCtx.style->colors[MU_COLOR_BORDER]      = color_to_mu(TAUPE_GRAY);
        muCtx.style->colors[MU_COLOR_WINDOWBG]    = color_to_mu(WARM_CREAM);
        muCtx.style->colors[MU_COLOR_TITLEBG]     = color_to_mu(ALABASTER_GRAY);
        muCtx.style->colors[MU_COLOR_TITLETEXT]   = color_to_mu(ESPRESSO_BLACK);
        muCtx.style->colors[MU_COLOR_PANELBG]     = color_to_mu(ALABASTER_GRAY);
        muCtx.style->colors[MU_COLOR_BUTTON]      = color_to_mu(ALABASTER_GRAY);
        muCtx.style->colors[MU_COLOR_BUTTONHOVER] = color_to_mu(CASHMERE_GRAY);
        muCtx.style->colors[MU_COLOR_BUTTONFOCUS] = color_to_mu(SLATE_BLUE);
        muCtx.style->colors[MU_COLOR_BASE]        = color_to_mu(ALABASTER_GRAY);
        muCtx.style->colors[MU_COLOR_BASEHOVER]   = color_to_mu(CASHMERE_GRAY);
        muCtx.style->colors[MU_COLOR_BASEFOCUS]   = color_to_mu(SLATE_BLUE);
        muCtx.style->colors[MU_COLOR_SCROLLBASE]  = color_to_mu(WARM_CREAM);
        muCtx.style->colors[MU_COLOR_SCROLLTHUMB] = color_to_mu(TAUPE_GRAY);
    }
}

void
init_ui()
{
    /* Init Hagl */
    display = hagl_init();
    /* Wire up the internal Pointer */
    muCtx.style = &muCtx._style;

    /* Init micro UI */
    mu_init(&muCtx);

    /* Wire up the callbacks */
    muCtx.text_width  = get_text_width;
    muCtx.text_height = get_text_height;

    /* Wire up the styles */
    muCtx.style->size           = (mu_Vec2) { 68, 18 };
    muCtx.style->padding        = 5;
    muCtx.style->spacing        = 4;
    muCtx.style->indent         = 12;
    muCtx.style->title_height   = 20;
    muCtx.style->scrollbar_size = 10;

    /* Use the 6x9 hagl inbuilt font */
    muCtx.style->font = (mu_Font)font6x9;

    /* Set dark Mode */
    apply_theme();
    ESP_LOGI(TAG, "Initialize ILI9341 display and UI");
}

void
render_microui()
{
    /* Clear Screen */
    hagl_clear(display);

    /* Iterate throught the command que */
    mu_Command *cmd = NULL;
    while (mu_next_command(&muCtx, &cmd))
    {
        switch (cmd->type)
        {
            case MU_COMMAND_RECT: {
                hagl_color_t col = hagl_color(display,
                                              cmd->rect.color.r,
                                              cmd->rect.color.g,
                                              cmd->rect.color.b);
                hagl_fill_rectangle(display,
                                    cmd->rect.rect.x,
                                    cmd->rect.rect.y,
                                    cmd->rect.rect.x + cmd->rect.rect.w - 1,
                                    cmd->rect.rect.y + cmd->rect.rect.h - 1,
                                    col);
                break;
            }
            /* TODO: Use hagl_put_text */
            case MU_COMMAND_TEXT: {
                hagl_color_t col = display->color(display,
                                                  cmd->text.color.r,
                                                  cmd->text.color.g,
                                                  cmd->text.color.b);
                char        *str = cmd->text.str;
                int16_t      x   = cmd->text.pos.x;
                int16_t      y   = cmd->text.pos.y;
                while (*str)
                {
                    wchar_t wch = (wchar_t)(uint8_t)*str++;
                    x += hagl_put_char(display, wch, x, y, col, font6x9);
                }

                break;
            }
            /* Hardcoded for 16x16 icons */
            case MU_COMMAND_ICON: {
                int id = cmd->icon.id;
                if (id >= ICON_NUMS)
                {
                    break;
                }
                /* All of our icons are packed into uint8_t buffers */
                static hagl_color_t icon_buffer[ICON_SIZE * 8];
                const uint8_t      *icon_data = globalIcons[id];
                hagl_color_t        col = display->color(display,
                                                         cmd->icon.color.r,
                                                         cmd->icon.color.g,
                                                         cmd->icon.color.b);

                /* Create the colored bitmap from alpha only data */
                for (uint16_t byte_idx = 0; byte_idx < ICON_SIZE; byte_idx++)
                {
                    uint8_t data_byte = icon_data[byte_idx];
                    uint16_t pixel_offset = byte_idx * 8;

                    icon_buffer[pixel_offset + 0] = (data_byte & 0x80) ? col : 0x0000;
                    icon_buffer[pixel_offset + 1] = (data_byte & 0x40) ? col : 0x0000;
                    icon_buffer[pixel_offset + 2] = (data_byte & 0x20) ? col : 0x0000;
                    icon_buffer[pixel_offset + 3] = (data_byte & 0x10) ? col : 0x0000;
                    icon_buffer[pixel_offset + 4] = (data_byte & 0x08) ? col : 0x0000;
                    icon_buffer[pixel_offset + 5] = (data_byte & 0x04) ? col : 0x0000;
                    icon_buffer[pixel_offset + 6] = (data_byte & 0x02) ? col : 0x0000;
                    icon_buffer[pixel_offset + 7] = (data_byte & 0x01) ? col : 0x0000;
                }
                /* Populate a hagl_bitmap buffer and use it to blit */
                hagl_bitmap_t src;
                uint8_t native_depth = sizeof(hagl_color_t) * 8;
                hagl_bitmap_init(&src, 16, 16, native_depth, icon_buffer);

                src.color = display->color;

                if (display->blit)
                {
                    display->blit(
                        display, cmd->icon.rect.x, cmd->icon.rect.y, &src);
                }
                break;
            }

            case MU_COMMAND_CLIP: {
                mu_Rect r = cmd->clip.rect;
                hagl_set_clip(display, r.x, r.y, r.x + r.w - 1, r.y + r.h - 1);
                break;
            }
        }
    }
    /* Reset clipping region to fullscreen before flushing */
    hagl_set_clip(display, 0, 0, display->width - 1, display->height - 1);
    /* Flush to SPI */
    hagl_flush(display);
}
