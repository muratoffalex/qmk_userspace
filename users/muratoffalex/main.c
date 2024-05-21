// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your optionany later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "main.h"

// Additional Features double tap guard (tap dance)

enum {
    U_TD_BOOT,
    U_TD_ESC,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
    [U_TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_ESC),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_BASE] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_BASE_QWERTY ),
    [U_EXTRA] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_BASE_COLEMAK ),
    [U_TAP] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_TAP_QWERTY ),
    [U_BUTTON] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_BUTTON ),
    [U_NAV] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_NAV ),
    [U_MOUSE] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_MOUSE ),
    [U_MEDIA] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_MEDIA ),
    [U_NUM] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_NUM ),
    [U_SYM] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_SYM ),
    [U_FUN] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_FUN ),
    [U_GAME] = U_MACRO_VA_ARGS( MIRYOKU_MAPPING,MIRYOKU_LAYER_GAME )
};


// combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
#endif

// const uint16_t PROGMEM qw_left_brace[] = {LGUI_T(KC_A), LALT_T(KC_S), COMBO_END};
// const uint16_t PROGMEM qw_right_brace[] = {LALT_T(KC_S), LCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM qw_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM qw_esc_num[] = {TD(U_TD_U_TAP), TD(U_TD_U_EXTRA), COMBO_END};
combo_t key_combos[] = {
    COMBO(qw_esc, LT(U_MEDIA,KC_ESC)),
    COMBO(qw_esc, KC_ESC),
    // COMBO(qw_left_brace, KC_LBRC),
    // COMBO(qw_right_brace, KC_RBRC),
    #if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
      COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
      COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
      COMBO(thumbcombos_nav, KC_DEL),
      COMBO(thumbcombos_mouse, KC_BTN3),
      COMBO(thumbcombos_media, KC_MUTE),
      COMBO(thumbcombos_num, KC_DOT),
      COMBO(thumbcombos_sym, KC_LPRN),
      COMBO(thumbcombos_fun, KC_APP)
    #endif
};

// shift functions
// key_overrides
const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};

// caps word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_SCLN:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


#ifdef OLED_ENABLE
#include "oled_features.c"
#endif
