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

#include QMK_KEYBOARD_H

#include "custom_shortcuts.h"

extern os_t os;

process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record) {

    bool isWindowsOrLinux = os.type == WINDOWS || os.type == LINUX;
    bool isOneShotShift = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isShifted = isOneShotShift || get_mods() & MOD_MASK_SHIFT;

    switch (keycode) {

        // Shift+Backspace for Delete (when not one-shot)

        case KC_BSPC:
        case RAI_BSP:
            if (record->event.pressed) {
                if (isShifted && !isOneShotShift) {
                    tap_code(KC_DEL);
                    return PROCESS_RECORD_RETURN_FALSE;
                }
            }
            return PROCESS_RECORD_RETURN_TRUE;

        // Ignore space for one-shot shift

        case LOW_SPC:
        case KC_SPC:
            if (record->event.pressed) {
                if (isOneShotShift) {
                    tap_code(KC_SPC);
                    add_oneshot_mods(MOD_LSFT);
                    return PROCESS_RECORD_RETURN_FALSE;
                }
            }
            return PROCESS_RECORD_CONTINUE;

        // Zoom shortcuts

        case SS_MODP:
            if (record->event.pressed) {
                if (should_send_ctrl(isWindowsOrLinux, isOneShotShift)) {
                    SEND_STRING(SS_LCTL("+"));
                } else {
                    SEND_STRING(SS_LGUI("+"));
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;
        case SS_MODM:
            if (record->event.pressed) {
                if (should_send_ctrl(isWindowsOrLinux, isOneShotShift)) {
                    SEND_STRING(SS_LCTL("-"));
                } else {
                    SEND_STRING(SS_LGUI("-"));
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

    }

    return PROCESS_RECORD_CONTINUE;
}
