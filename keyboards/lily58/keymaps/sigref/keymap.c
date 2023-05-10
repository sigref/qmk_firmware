#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _SWITCH,
  _DAVINCI,
  _DR_MED,
  _DR_CUT,
  _DR_EDT,
  _DR_FSN,
  _DR_COL,
  _DR_FLT,
  _GRYPH,
  _MOVE,
  _DR_LL,
  _DR_LR,
};

enum custom_keycodes {
  DF_SWITCH = SAFE_RANGE,
  DF_QWERTY,
  DF_DAVINCI,
  DR_PG_MED,
  DR_PG_CUT,
  DR_PG_EDT,
  DR_PG_FSN,
  DR_PG_COL,
  DR_PG_FLT,
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

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |GRYPH | /Space  /       \Enter \  | MOVE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
           KC_LALT, KC_LGUI, LT(_GRYPH, KC_LNG2),    KC_SPC,   KC_ENT,   LT(_MOVE, KC_LNG1), KC_BSPC, KC_RALT

),
/* GRYPH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |GRYPH | /Space  /       \Enter \  |LEADER| DEL  | RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_GRYPH] = LAYOUT(
  KC_ESC,  _______, _______, _______, _______, _______,                   _______,     _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______, DF_SWITCH, KC_DEL, _______
),
/* MOVE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      | HOME |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |      |      |                    |      |      |      |      | END  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL | Left | Down |Right |      |      |-------.    ,-------| Left | Down |  Up  |Right | PgUp |RCTRL |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|      |      |      |      | PgDn |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LEADER| /Space  /       \Enter \  | MOVE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_MOVE] = LAYOUT(
  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, XXXXXXX,
  _______, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  XXXXXXX,
  _______, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, XXXXXXX,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_PGUP, KC_RCTL,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, _______,
                             _______, _______, DF_SWITCH, XXXXXXX, XXXXXXX, _______, _______, _______
),

[_SWITCH] = LAYOUT(
  QK_RBT,  XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, QK_BOOT,                   QK_RBT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  XXXXXXX, DF_QWERTY, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  CL_TOGG, XXXXXXX,     XXXXXXX, DF_DAVINCI, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_DAVINCI] = LAYOUT(
  KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,         XXXXXXX,                                XXXXXXX,              XXXXXXX,         XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX,
  KC_TAB,   XXXXXXX, KC_UP,   XXXXXXX,        XXXXXXX,         XXXXXXX,                                XXXXXXX,              XXXXXXX,         XXXXXXX,       XXXXXXX, XXXXXXX,  S(KC_R),
  KC_LCTRL, KC_LEFT, KC_DOWN, KC_RIGHT,       XXXXXXX,         XXXXXXX,                                XXXXXXX,              KC_LEFT,         KC_DOWN,       KC_UP,   KC_RIGHT, C(KC_R),
  KC_LSFT,  XXXXXXX, C(KC_X), C(KC_C),        C(KC_V),         XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,         XXXXXXX,       XXXXXXX, XXXXXXX,  TD(TD_SPL_SPLFRZ),
                              LALT_T(KC_DEL), LALT_T(KC_BSPC), LT(_DR_LL, KC_LANG2), KC_SPC,  KC_ENT,  LT(_DR_LR, KC_LANG1), RALT_T(KC_BSPC), RALT_T(KC_DEL)
),

[_DR_LL] = LAYOUT(
  DR_PG_MED, DR_PG_CUT, DR_PG_EDT, DR_PG_FSN, DR_PG_COL, DR_PG_FLT,                   DR_PG_MED,   DR_PG_CUT, DR_PG_EDT, DR_PG_FSN, DR_PG_COL, DR_PG_FLT,
  _______,   _______,   _______,   _______,   _______,   _______,                     _______,     _______,   _______,   _______,   _______,   _______,
  _______,   _______,   _______,   _______,   _______,   _______,                     _______,     _______,   _______,   _______,   _______,   _______,
  _______,   _______,   _______,   _______,   _______,   _______,   _______, _______, _______,     _______,   _______,   _______,   _______,   _______,
                                   _______,   _______,   _______,   _______, _______, DF_SWITCH, _______,   _______
),

[_DR_LR] = LAYOUT(
  DR_PG_MED, DR_PG_CUT, DR_PG_EDT, DR_PG_FSN, DR_PG_COL, DR_PG_FLT,                     DR_PG_MED, DR_PG_CUT, DR_PG_EDT, DR_PG_FSN, DR_PG_COL, DR_PG_FLT,
  _______,   _______,   _______,   _______,   _______,   _______,                       _______,   _______,   _______,   _______,   _______,   _______,
  _______,   _______,   _______,   _______,   _______,   _______,                       _______,   _______,   _______,   _______,   _______,   _______,
  _______,   _______,   _______,   _______,   _______,   _______,     _______, _______, _______,   _______,   _______,   _______,   _______,   _______,
                                   _______,   _______,   DF_SWITCH, _______, _______, _______,   _______,   _______
),

[_DR_MED] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______,       _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______,       _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______,       _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, TD(TD_CN_CSN), _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______,       _______, _______
),

[_DR_CUT] = LAYOUT(
  C(S(KC_A)), _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______
),

[_DR_EDT] = LAYOUT(
  _______, _______, _______, _______,     _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,     _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,     _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, TD(TD_C_AC), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             S(KC_BSPC),  KC_BSPC, _______, S(KC_Z), _______, _______, KC_BSPC, S(KC_BSPC)
),

[_DR_FSN] = LAYOUT(
  KC_F5,   KC_F6,      KC_F7,   KC_F8,       KC_F9,     KC_F11,                      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F11,
  _______, _______,    _______, _______,     _______,   _______,                     _______, _______, _______, _______, _______, _______,
  _______, C(KC_LEFT), _______, C(KC_RIGHT), S(KC_SPC), _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______,    _______, _______,     _______,   _______, _______,   _______, _______, _______, _______, _______, _______, _______,
                                _______,     _______,   _______, S(KC_SPC), _______, _______, _______, _______
),

[_DR_COL] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

[_DR_FLT] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
)
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _GRYPH, _MOVE, _SWITCH);
// }

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
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

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    if (IS_LAYER_ON(_GRYPH)) {
      layer_name = "Layer: GRYPH";
    } else if (IS_LAYER_ON(_MOVE)) {
      layer_name = "Layer: MOVE";
    } else if (IS_LAYER_ON(_DR_LL)) {
      layer_name = "Layer: DR_LL";
    } else if (IS_LAYER_ON(_DR_LR)) {
      layer_name = "Layer: DR_RR";
    } else if (IS_LAYER_ON(_DR_MED)) {
      layer_name = "Layer: DR_MEDIA";
    } else if (IS_LAYER_ON(_DR_CUT)) {
      layer_name = "Layer: DR_CUT";
    } else if (IS_LAYER_ON(_DR_EDT)) {
      layer_name = "Layer: DR_EDIT";
    } else if (IS_LAYER_ON(_DR_FSN)) {
      layer_name = "Layer: DR_FUSION";
    } else if (IS_LAYER_ON(_DR_COL)) {
      layer_name = "Layer: DR_COLOR";
    } else if (IS_LAYER_ON(_DR_FLT)) {
      layer_name = "Layer: DR_FAIRLIGHT";
    } else {
      layer_name = default_layer_name;
    }
    oled_write_ln(layer_name, false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
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
    case DF_DAVINCI:
      if (record->event.pressed) {
#ifdef OLED_ENABLE
        default_layer_name = "Layer: D_RESOLVE";
#endif
        default_layer_set(_DAVINCI);
        layer_move(_DAVINCI);
      }
      return false;
    case DR_PG_MED:
      if (record->event.pressed) {
        tap_code16(S(KC_2));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_MED);
        layer_on(ln);
      }
      return false;
    case DR_PG_CUT:
      if (record->event.pressed) {
        tap_code16(S(KC_3));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_CUT);
        layer_on(ln);
      }
      return false;
    case DR_PG_EDT:
      if (record->event.pressed) {
        tap_code16(S(KC_4));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_EDT);
        layer_on(ln);
      }
      return false;
    case DR_PG_FSN:
      if (record->event.pressed) {
        tap_code16(S(KC_5));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_FSN);
        layer_on(ln);
      }
      return false;
    case DR_PG_COL:
      if (record->event.pressed) {
        tap_code16(S(KC_6));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_COL);
        layer_on(ln);
      }
      return false;
    case DR_PG_FLT:
      if (record->event.pressed) {
        tap_code16(S(KC_7));
        uint8_t ln = IS_LAYER_ON(_DR_LL) ? _DR_LL : _DR_LR;
        layer_move(_DR_FLT);
        layer_on(ln);
      }
      return false;
  }

  return true;
}

void leader_start_user(void) {
    }

void leader_end_user(void) {
  if (leader_sequence_four_keys(KC_T, KC_E, KC_S, KC_T)) {
    SEND_STRING("QMK leader key test.");
  } else if (leader_sequence_one_key(KC_LCTL)) {
      tap_code(KC_CAPS);
  }
}
