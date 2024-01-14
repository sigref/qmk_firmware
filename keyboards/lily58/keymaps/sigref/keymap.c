#include QMK_KEYBOARD_H
#include "layer.c"
#include "leader.c"
#include "oled.c"
#include "tapdance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                  KC_LALT, KC_LGUI, LT(_GRYPH, KC_LNG2), KC_SPC,  KC_ENT,   LT(_MOVE, KC_LNG1), KC_BSPC, KC_RALT
    ),

    [_GAME] = LAYOUT(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_M,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                    KC_LALT, KC_LGUI, LT(_GRYPH, KC_LNG2), KC_SPC,  KC_ENT,   LT(_MOVE, KC_LNG1), KC_BSPC, KC_RALT
    ),

    [_GRYPH] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______,                   _______,     _______, _______,_______, _______, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        QK_GESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
        _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                _______, _______, _______, _______, _______, XXXXXXX,     KC_DEL, _______
    ),

    [_MOVE] = LAYOUT(
        KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, XXXXXXX,
        _______, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  XXXXXXX,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, XXXXXXX,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_PGUP, KC_RCTL,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, _______,
                                _______, _______,  XXXXXXX,     XXXXXXX, XXXXXXX, _______, _______, _______
    ),

    [_SWITCH] = LAYOUT(
        QK_RBT,  XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, QK_BOOT,                   QK_RBT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CL_TOGG, XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

};
