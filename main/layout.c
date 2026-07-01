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
#include "icons.h"
#include "layout.h"
#include "graphic.h"

/* Generate the Menu entry functions at compile time */
#define MAIN_MENU_SUFFIX_LIST \
    X(WIFI)              \
    X(TOOLS)             \
    X(SETTINGS)          \
    X(BLE)               \
    X(GPS)               \
    X(IR)                \
    X(RFID)              \
    X(ABOUT)             \
    X(SUB_GHZ)

/* Generate all the inline functions */
#define X(suffix)                                 \
    static inline void set##suffix##Menu(void)    \
    {                                             \
        globalUIStateBuffer.page = PAGE_MENU;     \
        globalUIStateBuffer.menu = MENU_##suffix; \
    }
MAIN_MENU_SUFFIX_LIST

#undef X
#undef MAIN_MENU_SUFFIX_LIST

/* Start from the main page */
ui_state_t globalUIState = {
    .page    = PAGE_MENU,
    .feature = FEATURE_MAIN,
    .menu    = MENU_MAIN,
    .change  = false,
};

ui_state_t globalUIStateBuffer = {
    .page    = PAGE_MENU,
    .feature = FEATURE_MAIN,
    .menu    = MENU_MAIN,
    .change  = false,
};

/* global menu entry list */
const main_menu_entry_t globalMainMenuEntries[MENU_MAX_NUM] = {
    {
        .label   = "WiFi Menu",
        .icon_id = ICON_WIFI,
        .id      = MENU_WIFI,
        .onEntry = setWIFIMenu,
    },

    {
        .label   = "Tools",
        .icon_id = ICON_TOOLS,
        .id      = MENU_TOOLS,
        .onEntry = setTOOLSMenu,
    },

    {
        .label   = "Settings",
        .icon_id = ICON_SETTINGS,
        .id      = MENU_SETTINGS,
        .onEntry = setSETTINGSMenu,
    },

    {
        .label   = "BLE Menu",
        .icon_id = ICON_BLE,
        .id      = MENU_BLE,
        .onEntry = setBLEMenu,
    },

    {
        .label   = "GPS Menu",
        .icon_id = ICON_GPS,
        .id      = MENU_GPS,
        .onEntry = setGPSMenu,
    },

    {
        .label   = "IR Menu",
        .icon_id = ICON_IR,
        .id      = MENU_IR,
        .onEntry = setIRMenu,
    },

    {
        .label   = "RFID Menu",
        .icon_id = ICON_RFID,
        .id      = MENU_RFID,
        .onEntry = setRFIDMenu,
    },

    {
        .label   = "About",
        .icon_id = ICON_ABOUT,
        .id      = MENU_ABOUT,
        .onEntry = setABOUTMenu,
    },

    {
        .label   = "Sub GHZ Menu",
        .icon_id = ICON_SUBGHZ,
        .id      = MENU_SUB_GHZ,
        .onEntry = setSUB_GHZMenu,
    },

};

const menu_t mainMenu = {
    .entries   = MENU_MAX_NUM,
    .start_idx = 0,
};

const feature_menu_entry_t globalFeatureMenuEntries[FEATURE_MAX_NUM] = {

};

const menu_t featureMenu[] = {};
