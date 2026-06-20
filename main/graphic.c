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

#include "render.h"
#include "touch.h"
#include "graphic.h"
#include "config.h"
#include "layout.h"

/* Start from the main page */
ui_state_t globalUIState = {
    .page    = PAGE_MENU,
    .feature = FEATURE_MAIN,
    .menu    = MENU_MAIN,
};

void
ui_feature_menu()
{

    mu_Rect screenRect = mu_rect(0, 0, LCD_WIDTH, LCD_HEIGHT);
    /* Disable title close button and resize button */
    int windowFlags = MU_OPT_NOTITLE | MU_OPT_NORESIZE | MU_OPT_NOCLOSE;

    if (mu_begin_window_ex(&muCtx,
                           globalMainMenuEntries[globalUIState.menu].label,
                           screenRect,
                           windowFlags))
    {

        mu_layout_row(&muCtx, 1, (int[]) { -1 }, 30);

        int startIndx = featureMenu[globalUIState.menu].start_idx;
        int endIndx   = featureMenu[globalUIState.menu].entries + startIndx;
        for (int i = startIndx; i < endIndx; i++)
        {

            if (mu_button_ex(&muCtx,
                             globalFeatureMenuEntries[i].label,
                             globalFeatureMenuEntries[i].id,
                             0))
            {
                /* Update teh UI state according to the button pressed */
                if (globalFeatureMenuEntries[i].onEntry != NULL)
                {
                    globalFeatureMenuEntries[i].onEntry();
                }
            }
        }
        mu_end_window(&muCtx);
    }
}

void
ui_main_menu()
{

    mu_Rect screenRect = mu_rect(0, 0, LCD_WIDTH, LCD_HEIGHT);
    /* Disable title close button and resize button */
    int windowFlags = MU_OPT_NOTITLE | MU_OPT_NORESIZE | MU_OPT_NOCLOSE;

    if (mu_begin_window_ex(&muCtx, "ROOT_MENU", screenRect, windowFlags))
    {

        mu_Container *win         = mu_get_current_container(&muCtx);
        int           gap         = muCtx.style->spacing;
        int           sqHeight    = (win->body.w - gap) / 2;
        int           buttonFlags = 0;

        mu_layout_row(&muCtx, 2, (int[]) { -1, -1 }, sqHeight);
        /* Align the icon to button center */
        buttonFlags   = MU_OPT_ALIGNCENTER;
        int startIndx = mainMenu.start_idx;
        int endIndx   = mainMenu.entries + startIndx;
        for (int i = startIndx; i < endIndx; i++)
        {

            if (mu_button_ex(&muCtx,
                             globalMainMenuEntries[i].label,
                             globalMainMenuEntries[i].id,
                             buttonFlags))
            {
                /* Update teh UI state according to the button pressed */
                if (globalMainMenuEntries[i].onEntry != NULL)
                {
                    globalMainMenuEntries[i].onEntry();
                }
            }
        }
        mu_end_window(&muCtx);
    }
}

void
build_user_interface()
{
    switch (globalUIState.page)
    {
        /* If the page is menu */
        case PAGE_MENU: {
            /* Draw the menu */
            if(globalUIState.menu == MENU_MAIN)
                ui_main_menu();
            else
                ui_feature_menu();
            break;
        }
        case PAGE_LOADING: {
            break;
        }
        case PAGE_FEATURE: {
            switch (globalUIState.feature)
            {
                case FEATURE_MAIN: {
                    break;
                }
                case FEATURE_WIFI: {
                    break;
                }
                case FEATURE_TOOLS: {
                    break;
                }
                case FEATURE_SETTINGS: {
                    break;
                }
                case FEATURE_BLE: {
                    break;
                }
                case FEATURE_GPS: {
                    break;
                }
                case FEATURE_IR: {
                    break;
                }
                case FEATURE_RFID: {
                    break;
                }
                case FEATURE_ABOUT: {
                    break;
                }
                case FEATURE_SUB_GHZ: {
                    break;
                }
            }
        }
    }
}

void
ui_loop(void *pvParameters)
{
    bool last_touch = false;
    while (1)
    {
        touch_read(&last_touch);

        mu_begin(&muCtx);
        build_user_interface();
        mu_end(&muCtx);

        render_microui();

        vTaskDelay(pdMS_TO_TICKS(16));
    }
}
