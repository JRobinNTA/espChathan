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

#include "globals.h"
#include "config.h"
#include "icons.h"

#define TAG "UI"

extern hagl_backend_t *display;

extern mu_Context muCtx;

int
get_text_width(mu_Font font, const char *str, int len)
{
    return len * FONT_WIDTH;
}

int
get_text_height(mu_Font font)
{
    return FONT_HEIGHT;
}

void
get_draw_frame(mu_Context *ctx, mu_Rect rect, int colorid)
{
    mu_Color     c   = ctx->style->colors[colorid];
    hagl_color_t col = hagl_color(display, c.r, c.g, c.b);
    hagl_fill_rectangle(
        display, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, col);
}

void
init_ui()
{

    /* Init Hagl */
    display = hagl_init();
    /* Init micro UI */
    mu_init(&muCtx);
    /* Wire up the callbacks */
    muCtx.text_width  = get_text_width;
    muCtx.text_height = get_text_height;
    muCtx.draw_frame  = get_draw_frame;
    /* Use the 6x9 hagl inbuilt font */
    muCtx.style->font = (mu_Font)font6x9;
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

            case MU_COMMAND_TEXT: {
                hagl_color_t col = hagl_color(display,
                                              cmd->text.color.r,
                                              cmd->text.color.g,
                                              cmd->text.color.b);
                char        *str = cmd->text.str;
                while (*str)
                {
                    hagl_put_char(display,
                                  *str++,
                                  cmd->text.pos.x,
                                  cmd->text.pos.y,
                                  col,
                                  font6x9);
                    cmd->text.pos.x += 6;
                }

                break;
            }

            case MU_COMMAND_ICON: {
                int id = cmd->icon.id;
                if (id >= sizeof(icon_database) / sizeof(icon_database[0]))
                {
                    break;
                }
                hagl_bitmap_t src;
                src.width  = cmd->icon.rect.w;
                src.height = cmd->icon.rect.h;
                src.depth  = 16;
                src.pitch  = cmd->icon.rect.w * 2;
                src.buffer = (uint8_t *)icon_database[id];
                src.blit
                    = (void (*)(void *, int16_t, int16_t, void *))display->blit;
                src.scale_blit = (void (*)(
                    void *, int16_t, int16_t, uint16_t, uint16_t, void *))
                                     display->scale_blit;
                src.get_pixel  = display->get_pixel;
                src.put_pixel  = display->put_pixel;
                src.color      = display->color;
                src.hline      = display->hline;
                src.vline      = display->vline;

                src.clip.x0 = 0;
                src.clip.y0 = 0;
                src.clip.x1 = cmd->icon.rect.w - 1;
                src.clip.y1 = cmd->icon.rect.h - 1;

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
