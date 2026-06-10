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
#include <microui.h>
#include <esp_lcd_touch.h>

#include "lcDsply.h"
#include "touchScrn.h"
#include "graphicUI.h"

extern hagl_backend_t *display;

extern esp_lcd_touch_handle_t tp;

extern esp_lcd_panel_io_handle_t tp_io_handle;

extern mu_Context muCtx;

extern SemaphoreHandle_t spi_bus_mutex;

void build_user_interface(){

}

void ui_loop(void *pvParameters)
{
    bool last_touch = false;
    while (1) {
        touch_read(&last_touch);

        mu_begin(&muCtx);
        build_user_interface(); 
        mu_end(&muCtx);

        if (xSemaphoreTake(spi_bus_mutex, portMAX_DELAY) == pdTRUE) {
            render_microui();
            xSemaphoreGive(spi_bus_mutex);
        }

        vTaskDelay(pdMS_TO_TICKS(16)); 
    }
}
