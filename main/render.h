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
#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <microui.h>
#include <hagl.h>

typedef enum
{
    MUTED_PLUM     = 0x59AB,
    WARM_CREAM     = 0xFFBD,
    SAGE_GREEN     = 0x436A,
    ALABASTER_GRAY = 0xE71A,
    CASHMERE_GRAY  = 0xB574,
    CHARCOAL_BG    = 0x2945,
    TERRACOTTA     = 0xDB65,
    FOREST_GREEN   = 0x3468,
    ESPRESSO_BLACK = 0x10A2,
    MILKY_WHITE    = 0xF79D,
    TAUPE_GRAY     = 0x7B8D,
    SLATE_BLUE     = 0x2AB0,
    BRICK_RED      = 0xC1A5
} color_t;

typedef enum
{
    DARK,
    LIGHT
} theme_state_t;

extern theme_state_t   globalThemeState;
extern mu_Context      muCtx;
extern hagl_backend_t *display;

void apply_theme();

void init_ui();

void render_microui();

mu_Color color_to_mu(uint16_t rgb565);

#endif /* RENDER_H */
