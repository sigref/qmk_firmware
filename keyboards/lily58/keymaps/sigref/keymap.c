#include QMK_KEYBOARD_H

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif

enum Layer {
    L_DEFAULT = 0,
    L_GRYPH,
    L_MOVE,
    L_TRI,
};

enum CustomKeyCode {
    CK_GRV_ESC = SAFE_RANGE,
};

enum TapDanceKeyCode {
    TD_LBRC,
    TD_RBRC,
    TD_MIN_EQ,
    TD_SLS_BSLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_DEFAULT] = LAYOUT(
        CK_GRV_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                /**/              KC_6,    KC_7,    KC_8,    KC_9,   KC_0,            TD(TD_MIN_EQ),
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                /**/              KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,            KC_BSLS,
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                /**/              KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,         KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   TD(TD_LBRC), /**/ TD(TD_RBRC), KC_N,    KC_M,    KC_COMM, KC_DOT, TD(TD_SLS_BSLS), KC_RSFT,
                        KC_LALT, KC_LGUI, LT(L_GRYPH, KC_LNG2), KC_SPC,      /**/ KC_ENT,      LT(L_MOVE, KC_LNG1), KC_BSPC, KC_DEL
    ),

    [L_GRYPH] = LAYOUT(
        _______,    _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
        KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            /**/          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        CK_GRV_ESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          /**/          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
        _______,    _______, _______, _______, _______, _______, _______, /**/ _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                      QK_BOOT, _______, _______, _______, /**/ _______, _______, KC_MENU, KC_RALT
    ),

    [L_MOVE] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,     KC_4,    KC_5,             /**/          KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    XXXXXXX,
        _______, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,          /**/          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, KC_RCTL,
        _______, KC_HOME, KC_END,  KC_PGUP,  KC_PGDN, XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, KC_HOME, KC_END,  KC_PGUP,  KC_PGDN, _______,
                                   _______,  _______, _______, XXXXXXX, /**/ XXXXXXX, _______, XXXXXXX, QK_BOOT
    ),

    [L_TRI] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS,
        DM_RSTP, DM_REC1, DM_REC2, XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGUP,
        KC_CAPS, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  KC_END,  KC_PGDN,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, _______, XXXXXXX, /**/ XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),
};

#pragma region layer_state_set_user
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, L_GRYPH, L_MOVE, L_TRI);
  return state;
}
#pragma endregion

#pragma region process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CK_GRV_ESC) {
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_GRV);
            return false;
        } else if (record->event.pressed) {
            tap_code16(KC_ESC);
            return false;
        }
    }

    return true;
}
#pragma endregion

#pragma region oled
// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

const char *read_logo(void);
void render_space(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        oled_write(read_logo(), false);
    } else {
        render_space(); // Call this to render the space stuff on the one screen
    }
    return false;
}

// https://github.com/JBaguley/qmk_firmware/blob/c653e0f22f99828d0a14f10047a11f162772d6da/keyboards/crkbd/keymaps/retrograde/keymap.c
// Spaceship OLED Code Starts Here

unsigned int state = 0;

const char PROGMEM space_row_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x38, 0x38,
    0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x03, 0x03, 0x1f, 0xff,
    0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00,
    0xf8, 0xfc, 0xe6, 0xb2, 0x3e, 0xbe, 0xfe, 0xec, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
    0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x38, 0x38,
    0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x03, 0x03, 0x1f, 0xff,
    0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM space_row_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0xc0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x38, 0x00, 0x00, 0x03, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x06, 0x07, 0x05, 0x03, 0x00, 0x00,
    0x00, 0x01, 0x03, 0x03, 0x02, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x40, 0x60, 0x20, 0x20,
    0x38, 0x3f, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0xc0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x38, 0x00, 0x00, 0x03, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM space_row_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f,
    0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x38, 0x3c, 0x7c, 0xfc, 0xfc,
    0xfc, 0xfe, 0xfe, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0xe0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x0e, 0x0e, 0x02, 0x02, 0x03, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x30,
    0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f,
    0x7f, 0x7c, 0x7c, 0x7c, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x38, 0x3c, 0x7c, 0xfc, 0xfc,
    0xfc, 0xfe, 0xfe, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0xe0, 0xc0, 0x00, 0x00
};

const char PROGMEM space_row_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0e, 0x0e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x1e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x38, 0x31, 0x71, 0x70, 0x30, 0x3c, 0x1f,
    0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x01, 0x03, 0x03, 0x02, 0x02, 0x06, 0x04, 0x04, 0x0c, 0x0c, 0x08, 0x18, 0x18,
    0x10, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x07, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7e, 0x7e, 0x7c, 0x3c, 0x3c, 0x1c, 0x1c, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x38, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0e, 0x0e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x1e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x38, 0x31, 0x71, 0x70, 0x30, 0x3c, 0x1f,
    0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00
};

const char PROGMEM ship_row_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM ship_row_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x3e, 0x7c, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM ship_row_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1e, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM ship_row_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM mask_row_1[] = {
    0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const char PROGMEM mask_row_2[] = {
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f,
    0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const char PROGMEM mask_row_3[] = {
    0xff, 0xff, 0xff, 0xff, 0x3f, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0xf0,
    0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const char PROGMEM mask_row_4[] = {
    0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void render_space(void) {
    char wpm = get_current_wpm();
    char render_row[128];
    int i;
    oled_set_cursor(0, 0);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_1 + i + state);
    }
    for (i = wpm / 4; i < sizeof(render_row); i++) {
        render_row[i] = (pgm_read_byte(space_row_1 + i + state) & pgm_read_byte(mask_row_1 + i - wpm / 4)) | pgm_read_byte(ship_row_1 + i - wpm / 4);
    }

    oled_write_raw(render_row, sizeof(render_row));
    oled_set_cursor(0, 1);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_2 + i + state);
    }
    for (i = wpm / 4; i < sizeof(render_row); i++) {
        render_row[i] = (pgm_read_byte(space_row_2 + i + state) & pgm_read_byte(mask_row_2 + i - wpm / 4)) | pgm_read_byte(ship_row_2 + i - wpm / 4);
    }
    oled_write_raw(render_row, sizeof(render_row));
    oled_set_cursor(0, 2);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_3 + i + state);
    }
    for (i = wpm / 4; i < sizeof(render_row); i++) {
        render_row[i] = (pgm_read_byte(space_row_3 + i + state) & pgm_read_byte(mask_row_3 + i - wpm / 4)) | pgm_read_byte(ship_row_3 + i - wpm / 4);
    }

    oled_write_raw(render_row, sizeof(render_row));
    oled_set_cursor(0, 3);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_4 + i + state);
    }
    for (i = wpm / 4; i < sizeof(render_row); i++) {
        render_row[i] = (pgm_read_byte(space_row_4 + i + state) & pgm_read_byte(mask_row_4 + i - wpm / 4)) | pgm_read_byte(ship_row_4 + i - wpm / 4);
    }

    oled_write_raw(render_row, sizeof(render_row));

    state = (state + 1 + (wpm / 15)) % (sizeof(render_row) * 2);
}

#endif
#pragma endregion

#pragma region tapdance
#ifdef TAP_DANCE_ENABLE

#pragma region TD_LBRC
bool l_brackets_lshift_pressed = false;
bool l_brackets_rshift_pressed = false;
bool l_brackets_wip = false;

void dance_l_brackets_each(tap_dance_state_t *state, void *user_data) {
    if (!l_brackets_wip) {
        l_brackets_wip = true;
        l_brackets_lshift_pressed = (keyboard_report->mods & MOD_BIT_LSHIFT) != 0;
        l_brackets_rshift_pressed = (keyboard_report->mods & MOD_BIT_RSHIFT) != 0;
    }
}

void dance_l_brackets_finished(tap_dance_state_t *state, void *user_data) {
    unregister_mods(MOD_BIT_LSHIFT);
    unregister_mods(MOD_BIT_RSHIFT);

    if (state->count == 1) {
        if (!l_brackets_lshift_pressed && !l_brackets_rshift_pressed) {
            register_code16(KC_LPRN); // (
        } else {
            register_code16(KC_LABK); // <
        }
    } else {
        if (!l_brackets_lshift_pressed && !l_brackets_rshift_pressed) {
            register_code16(KC_LBRC); // [
        } else {
            register_code16(KC_LCBR); // {
        }
    }
}

void dance_l_brackets_reset(tap_dance_state_t *state, void *user_data) {
    l_brackets_wip = false;

    unregister_code16(KC_LPRN); // (
    unregister_code16(KC_LABK); // <
    unregister_code16(KC_LBRC); // [
    unregister_code16(KC_LCBR); // {

    if (l_brackets_lshift_pressed) {
        register_mods(MOD_BIT_LSHIFT);
    } else {
        unregister_mods(MOD_BIT_LSHIFT);
    }

    if (l_brackets_rshift_pressed) {
        register_mods(MOD_BIT_RSHIFT);
    } else {
        unregister_mods(MOD_BIT_RSHIFT);
    }
}
#pragma endregion

#pragma region TD_RBRC
bool r_brackets_lshift_pressed = false;
bool r_brackets_rshift_pressed = false;
bool r_brackets_wip = false;

void dance_r_brackets_each(tap_dance_state_t *state, void *user_data) {
    if (!r_brackets_wip) {
        r_brackets_wip = true;
        r_brackets_lshift_pressed = (keyboard_report->mods & MOD_BIT_LSHIFT) != 0;
        r_brackets_rshift_pressed = (keyboard_report->mods & MOD_BIT_RSHIFT) != 0;
    }
}

void dance_r_brackets_finished(tap_dance_state_t *state, void *user_data) {
    unregister_mods(MOD_BIT_LSHIFT);
    unregister_mods(MOD_BIT_RSHIFT);

    if (state->count == 1) {
        if (!r_brackets_lshift_pressed && !r_brackets_rshift_pressed) {
            register_code16(KC_RPRN); // )
        } else {
            register_code16(KC_RABK); // >
        }
    } else {
        if (!r_brackets_lshift_pressed && !r_brackets_rshift_pressed) {
            register_code16(KC_RBRC); // ]
        } else {
            register_code16(KC_RCBR); // }
        }
    }
}

void dance_r_brackets_reset(tap_dance_state_t *state, void *user_data) {
    r_brackets_wip = false;

    unregister_code16(KC_RPRN); // )
    unregister_code16(KC_RABK); // >
    unregister_code16(KC_RBRC); // ]
    unregister_code16(KC_RCBR); // }

    if (r_brackets_lshift_pressed) {
        register_mods(MOD_BIT_LSHIFT);
    } else {
        unregister_mods(MOD_BIT_LSHIFT);
    }

    if (r_brackets_rshift_pressed) {
        register_mods(MOD_BIT_RSHIFT);
    } else {
        unregister_mods(MOD_BIT_RSHIFT);
    }
}
#pragma endregion

tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(dance_l_brackets_each, dance_l_brackets_finished, dance_l_brackets_reset),
    [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(dance_r_brackets_each, dance_r_brackets_finished, dance_r_brackets_reset),
    [TD_MIN_EQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
    [TD_SLS_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};
#endif
#pragma endregion

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
