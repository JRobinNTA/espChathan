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
#include "esp_lcd_touch.h"
#include "config.h"

#define TAG "TOUCH"

extern esp_lcd_touch_handle_t tp;

extern esp_lcd_panel_io_handle_t tp_io_handle;

extern mu_Context muCtx;

void
init_touch()
{

    esp_lcd_panel_io_spi_config_t tp_io_config
        = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(TOUCH_CS_PIN);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
        (esp_lcd_spi_bus_handle_t)SPI2_HOST, &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = CONFIG_LCD_HRES,
        .y_max = CONFIG_LCD_VRES,
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
    bool pressed      = esp_lcd_touch_get_data(tp, &touchData, &count, 1);
    muCtx.mouse_pos   = (mu_Vec2) { touchData.x, touchData.y };
    muCtx.mouse_delta = (mu_Vec2) { touchData.x - muCtx.last_mouse_pos.x,
                                    touchData.y - muCtx.last_mouse_pos.y };

    /* 'mouse_down' is high while touching */
    muCtx.mouse_down = pressed ? MU_MOUSE_LEFT : 0;

    /* 'mouse_pressed' is high ONLY on the transition from 0 -> 1 */
    muCtx.mouse_pressed = (pressed && !(*last_touch_state)) ? MU_MOUSE_LEFT : 0;

    /* Save state for next frame */
    muCtx.last_mouse_pos = muCtx.mouse_pos;
    *last_touch_state    = pressed;
}
