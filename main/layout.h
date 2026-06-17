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
#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>

/* State var to track the current loaded page */
typedef enum
{
    PAGE_MENU,    /* Current Loaded page is a MENU */
    PAGE_FEATURE, /* Current Loaded page is a FEATURE */
    PAGE_LOADING, /* Current Loaded page is a LOADING Animation */
} ui_page_t;

/* State var to track the current loaded MENU only relevant if PAGE_MENU is set
 */
typedef enum
{
    MENU_NIL  = -1,
    MENU_MAIN = 0,
    MENU_WIFI,
    MENU_TOOLS,
    MENU_SETTINGS,
    MENU_BLE,
    MENU_GPS,
    MENU_IR,
    MENU_RFID,
    MENU_ABOUT,
    MENU_SUB_GHZ,
} ui_menu_t;

/* State var to track the current loaded FEATURE only relevant if PAGE_FEATURE
 * is set */
typedef enum
{
    FEATURE_NIL  = -1,
    FEATURE_MAIN = 0,
    FEATURE_WIFI,
    FEATURE_TOOLS,
    FEATURE_SETTINGS,
    FEATURE_BLE,
    FEATURE_GPS,
    FEATURE_IR,
    FEATURE_RFID,
    FEATURE_ABOUT,
    FEATURE_SUB_GHZ,
} ui_feature_t;

/* Struct to wrap the full UI state */
typedef struct
{
    ui_page_t    page;
    ui_menu_t    menu;
    ui_feature_t feature;
} ui_state_t;

/* A single menu entry */
typedef struct
{
    char          *label;
    uint8_t        id;
    void (*callback)(void);

} menu_entry_t;

/* Wraps a single menu from the global array of menu entries */
typedef struct
{
    const uint8_t start_idx;
    const uint8_t entries;
} menu_t;

extern const uint8_t     *globalIcons[];
extern ui_state_t         globalUIState;
extern const menu_entry_t globalEntries[];
extern const menu_t       globalMenus[];

#endif /* LAYOUT_H */
