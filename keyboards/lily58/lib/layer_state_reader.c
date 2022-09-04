
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_QWERTY 0
#define L_GRYPH (1 << 1)
#define L_MOVE (1 << 2)
#define L_NUMPAD (1 << 3)
#define L_NUMPAD_TRI (L_NUMPAD | L_MOVE | L_GRYPH)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    break;
  case L_MOVE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: MOVE");
    break;
  case L_GRYPH:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: GRYPH");
    break;
  case L_NUMPAD:
  case L_NUMPAD_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NUMPAD");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", layer_state);
  }

  return layer_state_str;
}
