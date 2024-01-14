#include QMK_KEYBOARD_H
#include "oled_animation.c"

enum layer_number {
    _QWERTY = 0,
    _GAME,
    _GRYPH,
    _MOVE,
    _SWITCH,
};

enum custom_keycodes {
    DF_SWITCH = SAFE_RANGE,
    DF_QWERTY,
    CAP_LCTL,
};

enum {
    TD_C_AC,
    TD_CN_CSN,
    TD_SPL_SPLFRZ,
};

void dance_bs_bsfrz_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(C(KC_BSLS));
    } else {
        tap_code16(C(KC_BSLS));
        wait_ms(50);
        tap_code16(C(KC_RIGHT));
        wait_ms(50);
        tap_code16(S(KC_R));
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_C_AC] = ACTION_TAP_DANCE_DOUBLE(KC_C, A(KC_C)),
    [TD_CN_CSN] = ACTION_TAP_DANCE_DOUBLE(C(KC_N), C(S(KC_N))),
    [TD_SPL_SPLFRZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bs_bsfrz_finished, NULL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                  KC_LALT, KC_LGUI, LT(_GRYPH, KC_LNG2), KC_SPC,  KC_ENT,   LT(_MOVE, KC_LNG1), KC_BSPC, KC_RALT
    ),

    [_GAME] = LAYOUT(
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_M,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                  KC_LALT, KC_LGUI, LT(_GRYPH, KC_LNG2), KC_SPC,  KC_ENT,   LT(_MOVE, KC_LNG1), KC_BSPC, KC_RALT
    ),

    [_GRYPH] = LAYOUT(
    KC_ESC,  _______, _______, _______, _______, _______,                   _______,     _______, _______,_______, _______, _______,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
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

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _GRYPH, _MOVE, _SWITCH);
// }

// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
// const char *read_layer_state(void); <- cannot use with changing default layer
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

char* default_layer_name = "Layer: DEFAULT";
const char* layer_name = "";

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        oled_write(read_logo(), false);
    } else {
        render_space(); // Call this to render the space stuff on the one screen
    }
    return false;
}
#endif // OLED_ENABLE

static uint8_t CAP_LCTL_PRESS_CNT = 0;
static uint16_t CAP_LCTL_PRESSED_TIME = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    // CAP_LCTLをダブルタップでCAPS送信
    if (keycode == CAP_LCTL) {
        if (record->event.pressed) {
            CAP_LCTL_PRESS_CNT += 1;
            CAP_LCTL_PRESSED_TIME = record->event.time;
            return false;
        } else {
            if (CAP_LCTL_PRESS_CNT > 0) {
                if (TIMER_DIFF_16(record->event.time, CAP_LCTL_PRESSED_TIME) < TAPPING_TERM) {
                    if (CAP_LCTL_PRESS_CNT >= 2) {
                        CAP_LCTL_PRESS_CNT = 0;
                        tap_code16(KC_CAPS);
                    }
                } else {
                    CAP_LCTL_PRESS_CNT = 0;
                    tap_code16(KC_LCTL);
                }
            }
            return false;
        }
    } else {
        CAP_LCTL_PRESS_CNT = 0;
    }

    switch (keycode) {
        case DF_SWITCH:
            if (record->event.pressed) {
#ifdef OLED_ENABLE
                default_layer_name = "Layer: SWITCH";
#endif
                default_layer_set(_SWITCH);
                layer_move(_SWITCH);
            }
            return false;
        case DF_QWERTY:
            if (record->event.pressed) {
#ifdef OLED_ENABLE
                default_layer_name = "Layer: DEFAULT";
#endif
                default_layer_set(_QWERTY);
                layer_move(_QWERTY);
            }
            return false;
    }

    return true;
}

void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_four_keys(KC_T, KC_E, KC_S, KC_T)) {
        SEND_STRING("QMK leader key test.");
    } else if (leader_sequence_one_key(KC_LCTL)) {
        tap_code(KC_CAPS);
    }
}
