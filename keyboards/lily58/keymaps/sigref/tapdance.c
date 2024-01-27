#include "tapdance.h"

#ifdef TAP_DANCE_ENABLE

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

tap_dance_action_t tap_dance_actions[] = {
    [TD_L_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(dance_l_brackets_each, dance_l_brackets_finished, dance_l_brackets_reset),
    [TD_R_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(dance_r_brackets_each, dance_r_brackets_finished, dance_r_brackets_reset),
    [TD_MIN_EQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
    [TD_SLS_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};

#endif
