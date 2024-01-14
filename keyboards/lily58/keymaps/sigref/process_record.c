#include "process_record.h"

uint8_t CAP_LCTL_PRESS_CNT = 0;
uint16_t CAP_LCTL_PRESSED_TIME = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
                default_layer_set(_SWITCH);
                layer_move(_SWITCH);
            }
            return false;
        case DF_QWERTY:
            if (record->event.pressed) {
                default_layer_set(_QWERTY);
                layer_move(_QWERTY);
            }
            return false;
    }

    return true;
}
