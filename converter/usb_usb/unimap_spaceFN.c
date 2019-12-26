/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "unimap_trans.h"

enum function_id {
  ESC_CAPS,
  SPC_CAPS,
};

enum macro_id {
  SCREEN_1,
  SCREEN_2,
  SCREEN_3,
  SCREEN_4
};

//#define AC_ESC_L1  ACTION_LAYER_TAP_KEY(1, KC_ESC)
//#define AC_SPC_L1  ACTION_LAYER_TAP_KEY(1, KC_SPC)
#define AC_ESC_L1  ACTION_FUNCTION_TAP(ESC_CAPS)
#define AC_SPC_L1  ACTION_FUNCTION_TAP(SPC_CAPS)
#define AC_SCR1    ACTION_MACRO(SCREEN_1)
#define AC_SCR2    ACTION_MACRO(SCREEN_2)
#define AC_SCR3    ACTION_MACRO(SCREEN_3)
#define AC_SCR4    ACTION_MACRO(SCREEN_4)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    UNIMAP(
              F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    GRV,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,         VOLD,VOLU,MUTE,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,
    ESC_L1,A, S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,                         P4,  P5,  P6,  PCMM,
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,          UP,           P1,  P2,  P3,  PENT,
    LCTL,LGUI,LALT,MHEN,          SPC_L1,        HENK,KANA,RALT,F11, F11, F11,      LEFT,DOWN,RGHT,    P0,       PDOT,PEQL
    ),
    /* space FN layer */
    UNIMAP(
              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS,
    TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS, DEL,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    SCR4,SCR1,SCR2,SCR3,WH_U,TRNS,PGDN,PGUP,HOME,END, PSCR,SLCK,PAUS,      INS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    CAPS,WH_L,BTN2,BTN3,BTN1,WH_R,LEFT,DOWN,UP,  RGHT,BSPC,DEL,      TRNS,TRNS,                        TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,WH_D,SPC, BTN1,PGDN,VOLD,VOLU,CALC,     TRNS,TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,     TRNS,TRNS
    ),
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case SCREEN_1:
            return (record->event.pressed ?
                    MACRO( T(CAPS), T(NLCK), T(NLCK), T(1), T(CAPS), END ) :
                    MACRO_NONE );
        case SCREEN_2:
            return (record->event.pressed ?
                    MACRO( T(CAPS), T(NLCK), T(NLCK), T(2), T(CAPS), END ) :
                    MACRO_NONE );
        case SCREEN_3:
            return (record->event.pressed ?
                    MACRO( T(CAPS), T(NLCK), T(NLCK), T(3), T(CAPS), END ) :
                    MACRO_NONE );
        case SCREEN_4:
            return (record->event.pressed ?
                    MACRO( T(CAPS), T(NLCK), T(NLCK), T(4), T(CAPS), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}


/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case ESC_CAPS:
        case SPC_CAPS:
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                } else {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                    layer_on(1);
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    register_code(id==ESC_CAPS?KC_ESC:KC_SPC);
                    unregister_code(id==ESC_CAPS?KC_ESC:KC_SPC);
                } else {
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                    layer_off(1);
                }
            }
            break;
    }
}

