#include QMK_KEYBOARD_H
#include "quantum.h"
#include "marek.c"

const uint16_t PROGMEM combo_capsword[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM combo_caps[]     = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM combo_bn[]       = {KC_B, KC_N, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {COMBO_ACTION(combo_capsword), COMBO(combo_caps, KC_CAPS)};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case 0:
            if (pressed) {
                caps_word_on(); // Activate Caps Word!
            }
            break;
    }
}
