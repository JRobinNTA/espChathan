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

/* Touch Pins for the XPT2046 driver */
#define TOUCH_CS_PIN  33
#define TOUCH_IRQ_PIN 36

/* LCD Resolution
 * If edit also update the vals in sdkconfig for the hagl_hal driver */
#define LCD_WIDTH 320
#define LCD_HEIGHT 240

/* Font used is font6x9 from hagl */
#define FONT_HEIGHT 9
#define FONT_WIDTH  6
