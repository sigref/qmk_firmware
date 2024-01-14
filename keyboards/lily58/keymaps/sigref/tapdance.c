#include "tapdance.h"

#ifdef TAP_DANCE_ENABLE

tap_dance_action_t tap_dance_actions[] = {
    [TD_C_AC] = ACTION_TAP_DANCE_DOUBLE(KC_C, A(KC_C)),
    [TD_CN_CSN] = ACTION_TAP_DANCE_DOUBLE(C(KC_N), C(S(KC_N))),
    [TD_SPL_SPLFRZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bs_bsfrz_finished, NULL),
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

#endif
