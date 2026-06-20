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

/* Represent the list of menus */
typedef enum
{
    MENU_MAIN = -1, /* Main Menu is the root menu exempt it */
    MENU_WIFI,
    MENU_TOOLS,
    MENU_SETTINGS,
    MENU_BLE,
    MENU_GPS,
    MENU_IR,
    MENU_RFID,
    MENU_ABOUT,
    MENU_SUB_GHZ,
    MENU_MAX_NUM,
} ui_menu_t;

/* Represent the List of Features */
typedef enum
{
    FEATURE_MAIN = -1, /* Feature Main is just the home page exempt it */
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

/* Root menu aka main indexes the main menu entries*/
typedef struct
{
    char     *label;
    uint8_t   icon_id;
    ui_menu_t id;
    void (*onEntry)(void);
} main_menu_entry_t;

/* Feature menu indexes the feature menu entries */
typedef struct
{
    char        *label;
    uint8_t      icon_id;
    ui_feature_t id;
    void (*onEntry)(void);
    void (*doUpdates)(void);
    void (*onExit)(void);
} feature_menu_entry_t;

typedef struct
{
    const uint8_t start_idx;
    const uint8_t entries;
} menu_t;

extern ui_state_t globalUIState;

extern const menu_t mainMenu;
extern const menu_t featureMenu[];

extern const feature_menu_entry_t globalFeatureMenuEntries[];
extern const main_menu_entry_t    globalMainMenuEntries[MENU_MAX_NUM];

#endif /* LAYOUT_H */
