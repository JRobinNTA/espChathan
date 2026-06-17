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

/* global icon list */
const uint8_t *globalIcons[] = {
    bitmapWiFi,
    bitmapTools,
    bitmapSettings,
    bitmapBLE,
    bitmapGPS,
    bitmapIR,
    bitmapRFID,
    bitmapAbout,
    bitmapSubGHZ,
};

void static inline setWiFi(void)
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_WIFI;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setTools()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_TOOLS;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setSettings()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_SETTINGS;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setBLE()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_BLE;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setGPS()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_GPS;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setIR()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_IR;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setRFID()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_BLE;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setAbout()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_GPS;
    globalUIState.feature = FEATURE_NIL;
}

void static inline setSubGHZ()
{
    globalUIState.page    = PAGE_MENU;
    globalUIState.menu    = MENU_IR;
    globalUIState.feature = FEATURE_NIL;
}

/* global menu entry list */
const menu_entry_t globalEntries[] = {
    { .label = "WiFi", .id = 0, .callback = setWiFi },
    { .label = "Tools", .id = 1, .callback = setTools },
    { .label = "Settings", .id = 2, .callback = setSettings },
    { .label = "BLE", .id = 3, .callback = setBLE },
    { .label = "GPS", .id = 4, .callback = setGPS },
    { .label = "IR", .id = 5, .callback = setIR },
    { .label = "RFID", .id = 6, .callback = setRFID },
    { .label = "About", .id = 7, .callback = setAbout },
    { .label = "Sub GHZ", .id = 8, .callback = setSubGHZ },
};

/* Main Menu */
const menu_t globalMenus[] = {
    { .start_idx = 0, .entries = 9},
    { .start_idx = 9, .entries = 2},
};
