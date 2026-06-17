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

#include <esp_log.h>
#include <esp_lcd_touch_xpt2046.h>
#include <microui.h>
#include <esp_lcd_touch.h>

#include "config.h"
#include "render.h"

#define TAG "TOUCH"

esp_lcd_touch_handle_t tp;

esp_lcd_panel_io_handle_t tp_io_handle;

void
init_touch()
{

    esp_lcd_panel_io_spi_config_t tp_io_config
        = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(TOUCH_CS_PIN);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
        (esp_lcd_spi_bus_handle_t)SPI2_HOST, &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = LCD_WIDTH,
        .y_max = LCD_HEIGHT,
        .rst_gpio_num = -1,
        .int_gpio_num = TOUCH_IRQ_PIN,
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };

    ESP_LOGI(TAG, "Initialize touch controller XPT2046");
    ESP_ERROR_CHECK(esp_lcd_touch_new_spi_xpt2046(tp_io_handle, &tp_cfg, &tp));
}

void
touch_read(bool *last_touch_state)
{
    esp_lcd_touch_point_data_t touchData;
    uint8_t                    count = 0;

    /* Update touch point data. */
    esp_lcd_touch_read_data(tp);
    bool pressed = esp_lcd_touch_get_data(tp, &touchData, &count, 1);
    if (pressed)
    {
        /* If we were already touching last frame, this is a drag operation */
        if (*last_touch_state)
        {
            /* Calculate how far the finger moved since the last frame */
            int delta_x = touchData.x - muCtx.mouse_pos.x;
            int delta_y = touchData.y - muCtx.mouse_pos.y;

            /* Apply a deadzone so tiny finger shakes don't trigger scrolling */
            if (abs(delta_y) > 2 || abs(delta_x) > 2)
            {
                /* Multiplying by a factor changes scrolling speed */
                mu_input_scroll(&muCtx, delta_x * 2, delta_y * 2);
            }
            mu_input_mousemove(&muCtx, touchData.x, touchData.y);

            /* Transitioning from unpressed to pressed so a click event*/
            if (!(*last_touch_state))
            {
                mu_input_mousedown(
                    &muCtx, touchData.x, touchData.y, MU_MOUSE_LEFT);
            }
        }
        else
        {
            /* Transitioning from pressed to unpressed so a release event */
            if (*last_touch_state)
            {
                mu_input_mouseup(&muCtx,
                                 muCtx.mouse_pos.x,
                                 muCtx.mouse_pos.y,
                                 MU_MOUSE_LEFT);
            }
        }
        *last_touch_state = pressed;
    }
}
