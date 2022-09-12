#include QMK_KEYBOARD_H

// enum layers {
//   _QWERTY,
//   _LOWER,
//   _RAISE,
//   _ADJUST
// };

// // Tap Dance declarations
// enum {
//     TD_LSHIFT_CAPS,
//     TD_RSHIFT_CAPS,
// };

#include "marek.c"

#if defined(RGB_MATRIX_ENABLE)
uint8_t LOWER_KEY = 5;
uint8_t RAISE_KEY = 6;


// // Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     [TD_LSHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_CAPS),
//     [TD_RSHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSHIFT, KC_CAPS),
// };

// void rgb_matrix_indicators_kb(void) {
//     switch(get_highest_layer(layer_state|default_layer_state)) {
//         case _LOWER:
//             rgb_matrix_enable_noeeprom();
//             rgb_matrix_set_color(LOWER_KEY, RGB_YELLOW);
//             break;
//         case _RAISE:
//             rgb_matrix_enable_noeeprom();
//             rgb_matrix_set_color(RAISE_KEY, RGB_MAGENTA);
//             break;
//         case _ADJUST:
//             rgb_matrix_enable_noeeprom();
//             rgb_matrix_set_color(LOWER_KEY, RGB_RED);
//             rgb_matrix_set_color(RAISE_KEY, RGB_RED);
//             break;
//     }
// }


const uint16_t PROGMEM combo_ei[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_vm[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM combo_bn[] = {KC_B, KC_N, COMBO_END};
// const uint16_t PROGMEM combo_af[] = {KC_A, KC_F, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO_ACTION(combo_vm),
    COMBO(combo_ei, KC_UNDS),
    COMBO(combo_bn, KC_CAPS)
    // COMBO(combo_af, KC_ESC)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case 0:
      if (pressed) {
        caps_word_on();  // Activate Caps Word!
      }
      break;
  }
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif
