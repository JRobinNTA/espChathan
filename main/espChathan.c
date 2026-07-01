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

#include <stdio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>

#include "render.h"
#include "touch.h"
#include "graphic.h"
#include "sdcard.h"
#define TAG "MAIN"

void
app_main(void)
{
    ESP_LOGI(TAG, "Booting system....");

    init_sdcard();
    init_ui();
    init_touch();
    xTaskCreatePinnedToCore(
        ui_loop,
        "UI_Task",
        4096,
        NULL,
        5,
        NULL,
        1
    );
}
