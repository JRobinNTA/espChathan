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
#include "icons.h"

void
ui_feature_main()
{
}

void
ui_loading()
{
}

void
ui_feature_menu()
{

    /* Leave the top 48 pixels for status bar and title bar */
    mu_Rect screenRect
        = mu_rect(0, 8, LCD_WIDTH, LCD_HEIGHT - TITLE_BAR_HEIGHT);
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
                /* Ignore repeated button mashes */
                if (!globalUIState.change)
                {
                    globalUIState.change = true;
                    /* Update teh UI state according to the button pressed */
                    if (globalFeatureMenuEntries[i].onEntry != NULL)
                    {
                        globalFeatureMenuEntries[i].onEntry();
                    }
                }
            }
        }
        mu_end_window(&muCtx);
    }
}

void
ui_main_menu()
{
    /* Leave the top 48 pixels for status bar and title bar */
    mu_Rect screenRect = mu_rect(
        0, TITLE_BAR_HEIGHT, LCD_WIDTH, LCD_HEIGHT - TITLE_BAR_HEIGHT);
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
                /* Ignore repeated button mashes */
                if (!globalUIState.change)
                {
                    globalUIState.change = true;
                    /* Update teh UI state according to the button pressed */
                    if (globalMainMenuEntries[i].onEntry != NULL)
                    {
                        globalMainMenuEntries[i].onEntry();
                    }
                }
            }
        }
        mu_end_window(&muCtx);
    }
}

void
ui_title_bar(void)
{
    mu_Rect barRect  = mu_rect(0, 0, LCD_WIDTH, TITLE_BAR_HEIGHT);
    int     barFlags = MU_OPT_NOTITLE | MU_OPT_NORESIZE | MU_OPT_NOCLOSE;
    if (mu_begin_window_ex(&muCtx, "ROOT_TITLE_BAR", barRect, barFlags))
    {
        mu_layout_row(&muCtx, 2, (int[]) { 36, -1 }, TITLE_BAR_HEIGHT - 10);
        if (mu_button_ex(&muCtx, " ", ICON_BACK, MU_OPT_ALIGNCENTER))
        {
            /* Ignore repeated button mashes */
            if (!globalUIState.change)
            {
                globalUIState.change = true;
                if (globalUIState.page == PAGE_FEATURE)
                {
                    /* buffer state always stores the last menu */
                    globalUIStateBuffer.menu = globalUIState.menu;
                    globalUIStateBuffer.page = PAGE_MENU;
                }
                else if (globalUIState.page == PAGE_MENU
                         && globalUIState.menu != MENU_MAIN)
                {
                    globalUIStateBuffer.menu = MENU_MAIN;
                    globalUIStateBuffer.page = PAGE_MENU;
                }
                else
                {
                    globalUIStateBuffer.feature = FEATURE_MAIN;
                    globalUIStateBuffer.page    = PAGE_FEATURE;
                }
            }
        }

        const char *titleText = "Main Menu";
        if (globalUIState.page == PAGE_MENU && globalUIState.menu != MENU_MAIN)
        {
            titleText = globalMainMenuEntries[globalUIState.menu].label;
        }
        else if (globalUIState.page == PAGE_FEATURE
                 && globalUIState.feature != FEATURE_MAIN)
        {
            titleText = globalFeatureMenuEntries[globalUIState.feature].label;
        }
        mu_button_ex(&muCtx, titleText, 0, MU_OPT_ALIGNCENTER | MU_OPT_NOFRAME);
        mu_Container *barWin = mu_get_current_container(&muCtx);
        mu_draw_rect(&muCtx,
                     mu_rect(barWin->body.x,
                             barWin->body.y + TITLE_BAR_HEIGHT - 1,
                             barWin->body.w,
                             1),
                     color_to_mu(ESPRESSO_BLACK));

        mu_end_window(&muCtx);
    }
}

void
build_user_interface()
{
    /* The globalUIStateBuffer is updated from the doUpdates renderer itself */
    if (globalUIState.change)
    {
        if (globalUIState.page == PAGE_FEATURE
            && globalUIState.feature != FEATURE_MAIN)
        {
            /* Call the destructors */
            globalFeatureMenuEntries[globalUIState.feature].onExit();
        }
        /* Safely update the UI state */
        globalUIState.feature = globalUIStateBuffer.feature;
        globalUIState.menu    = globalUIStateBuffer.menu;
        globalUIState.page    = globalUIStateBuffer.page;
        /* Release the guard */
        globalUIState.change = false;
    }
    switch (globalUIState.page)
    {
        case PAGE_MENU: {
            ui_title_bar();
            /* We are currently in main menu */
            if (globalUIState.menu == MENU_MAIN)
            {
                ui_main_menu();
            }

            /* We are currently in a feature menu */
            else
            {
                ui_feature_menu();
            }
            break;
        }
        case PAGE_LOADING:
            ui_loading();
            break;
        case PAGE_FEATURE: {
            if (globalUIState.feature == FEATURE_MAIN)
            {
                ui_feature_main();
            }
            else
            {

                ui_title_bar();
                globalFeatureMenuEntries[globalUIState.feature].doUpdates();
            }
            break;
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
