#include "leader.h"

#ifdef LEADER_ENABLE

void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_four_keys(KC_T, KC_E, KC_S, KC_T)) {
        SEND_STRING("QMK leader key test.");
    } else if (leader_sequence_one_key(KC_LCTL)) {
        tap_code(KC_CAPS);
    }
}

#endif
