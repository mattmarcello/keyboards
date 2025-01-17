/* Copyright 2021 Rafael Romão @rafaelromao
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include QMK_KEYBOARD_H

#include "../definitions/keycodes.h"
#include "os_toggle.h"
#include "default_mod_key.h"
#include "dynamic_macro.h"

enum {
    COM_LEA,
    INJ_LEF,
    INJ_RIG,
    SCL_END,
    BRT_CUR,
    BRT_SQR,
    BRT_PAR,
    BRT_ANG,
    DOT_DOT,
    SDB_QUO,
    DLR_CUR,
    UND_REC
};

#define TD_COML TD(COM_LEA)
#define TD_IJLE TD(INJ_LEF)
#define TD_IJRI TD(INJ_RIG)
#define TD_SCLE TD(SCL_END)
#define TD_CURB TD(BRT_CUR)
#define TD_SQRB TD(BRT_SQR)
#define TD_PARB TD(BRT_PAR)
#define TD_ANGB TD(BRT_ANG)
#define TD_DOTD TD(DOT_DOT)
#define TD_QUOT TD(SDB_QUO)
#define TD_DLR TD(DLR_CUR)
#define TD_UNDS TD(UND_REC)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    td_state_t state;
    bool recording;
} td_tap_t;

td_state_t dance_state(qk_tap_dance_state_t *state);
