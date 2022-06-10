/* Copyright 2020 imchipwood
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

enum custom_keycodes {
    UC_AL = USER00,
    UC_CN,
    UC_CO,
    UC_DI,
    UC_DL,
    UC_DR,
    UC_MV,
    UC_RM,
    UC_TL,
    UC_TR,
    UC_WA,
    UC_WN,
    UC_WT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |   Esc   |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |   Tab   |
    |-------------|---------|---------|---------|---------|
    | Left mouse  |  TT(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_7,      KC_8,    KC_9,     KC_BSPC,
                    KC_4,      KC_5,    KC_6,     KC_ESC,
                    KC_1,      KC_2,    KC_3,     KC_TAB,
        KC_BTN1,    TT(1),     KC_0,    KC_DOT,   KC_ENT
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    +    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |         |         |         |    =    |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    UC_WT,     UC_DL,     UC_AL,      _______,
                    UC_WA,     UC_WN,     UC_DR,      UC_TR,
                    UC_CN,     KC_UP,     UC_RM,      _______,
        KC_LOCK,    KC_LEFT,   KC_DOWN,   KC_RIGHT,   _______
    ),
    [2] = LAYOUT(
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
        KC_LOCK,    _______,     _______,     _______,      _______
    ),
    [3] = LAYOUT(
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
        _______,    _______,     _______,     _______,      _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
*/
  switch (keycode) {
    case UC_AL:
      if (record->event.pressed) {
        SEND_STRING("al");
      }
      break;
    case UC_CN:
      if (record->event.pressed) {
        SEND_STRING("cn");
      }
      break;
    case UC_CO:
      if (record->event.pressed) {
        SEND_STRING("co");
      }
      break;
    case UC_DI:
      if (record->event.pressed) {
        SEND_STRING("di");
      }
      break;
    case UC_DL:
      if (record->event.pressed) {
        SEND_STRING("dl");
      }
      break;
    case UC_DR:
      if (record->event.pressed) {
        SEND_STRING("dr");
      }
      break;
    case UC_MV:
      if (record->event.pressed) {
        SEND_STRING("mv");
      }
      break;
    case UC_RM:
      if (record->event.pressed) {
        SEND_STRING("rm");
      }
      break;
    case UC_TL:
      if (record->event.pressed) {
        SEND_STRING("tl");
      }
      break;
    case UC_TR:
      if (record->event.pressed) {
        SEND_STRING("tr");
      }
      break;
    case UC_WA:
      if (record->event.pressed) {
        SEND_STRING("wa");
      }
      break;
    case UC_WN:
      if (record->event.pressed) {
        SEND_STRING("wn");
      }
      break;
    case UC_WT:
      if (record->event.pressed) {
        SEND_STRING("wt");
      }
      break;
  }
  return true; // Process all other keycodes normally
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    /*  Custom encoder control - handles CW/CCW turning of encoder
     *  Default behavior:
     *    left encoder:
     *      main layer:
     *         CW: move mouse right
     *        CCW: move mouse left
     *      other layers:
     *         CW: = (equals/plus - increase slider in Adobe products)
     *        CCW: - (minus/underscore - decrease slider in adobe products)
     *    right encoder:
     *      main layer:
     *         CW: colume up
     *        CCW: volume down
     *      other layers:
     *         CW: right arrow
     *        CCW: left arrow
     */
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                // main layer - move mouse right (CW) and left (CCW)
                if (clockwise) {
                    tap_code(KC_MS_R);
                } else {
                    tap_code(KC_MS_L);
                }
                break;

            default:
                // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
                if (clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                // main layer - volume up (CW) and down (CCW)
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            default:
                // other layers - right (CW) and left (CCW)
                if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
                break;
        }
    }
    return true;
}
