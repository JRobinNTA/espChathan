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
#ifndef ICONS_H
#define ICONS_H

#define ICON_SIZE 32

#include <stdint.h>

/* Generated from bitmapScan.png */
extern const uint8_t bitmapScan[ICON_SIZE];

/* Generated from bitmapAbout.png */
extern const uint8_t bitmapAbout[ICON_SIZE];

/* Generated from bitmapRFID.png */
extern const uint8_t bitmapRFID[ICON_SIZE];

/* Generated from bitmapGPS.png */
extern const uint8_t bitmapGPS[ICON_SIZE];

/* Generated from bitmapTools.png */
extern const uint8_t bitmapTools[ICON_SIZE];

/* Generated from bitmapBLE.png */
extern const uint8_t bitmapBLE[ICON_SIZE];

/* Generated from bitmapWiFi.png */
extern const uint8_t bitmapWiFi[ICON_SIZE];

/* Generated from bitmapSubGHZ.png */
extern const uint8_t bitmapSubGHZ[ICON_SIZE];

/* Generated from bitmapSettings.png */
extern const uint8_t bitmapSettings[ICON_SIZE];

/* Generated from bitmapIR.png */
extern const uint8_t bitmapIR[ICON_SIZE];

/* Generated from bitmapBack.png */
extern const uint8_t bitmapBack[ICON_SIZE];

/* Icon index enumeration */
typedef enum {
    ICON_SCAN,
    ICON_ABOUT,
    ICON_RFID,
    ICON_GPS,
    ICON_TOOLS,
    ICON_BLE,
    ICON_WIFI,
    ICON_SUBGHZ,
    ICON_SETTINGS,
    ICON_IR,
    ICON_BACK,
    ICON_MAX_NUM
} icon_t;

/* Global array of all icon bitmaps */
extern const uint8_t *globalIcons[ICON_MAX_NUM];

#define ICON_NUMS 11

#endif /* ICONS_H */
