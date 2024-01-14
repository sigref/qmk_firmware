#pragma once

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"

enum {
    TD_C_AC,
    TD_CN_CSN,
    TD_SPL_SPLFRZ,
};

void dance_bs_bsfrz_finished(tap_dance_state_t *state, void *user_data);
