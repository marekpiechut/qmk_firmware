/* Copyright 2021 Marek Piechut - DayOne s.c.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "m1x.h"

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  1,  2,  3,  4,  5,      6,  7,  8,  9, 10, 11},
        {12, 13, 14, 15, 16, 17,     18, 19, 20, 21, 22, 23},
        {24, 25, 26, 27, 28, 29,     30, 31, 32, 33, 34, 35},
        {36, 37, 38, 39, 40, 41, NO_LED, 42, 43, 44, 45, 46}
    }, {
        // LED Index to Physical Position
        {  0,  0}, { 20,  0}, { 40,  0}, {61,  0}, {81,  0}, {101,  0}, {122,  0}, {142,  0}, {162,  0}, {183,  0}, {203,  0}, {224,  0},
        {  0, 21}, { 20, 21}, { 40, 21}, {61, 21}, {81, 21}, {101, 21}, {122, 21}, {142, 21}, {162, 21}, {183, 21}, {203, 21}, {224, 21},
        {  0, 42}, { 20, 42}, { 40, 42}, {61, 42}, {81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42},
        {  0, 64}, { 20, 64}, { 40, 64}, {61, 64}, {81, 64},       {111, 64},      {142, 64}, {162, 64}, {183, 64}, {203, 64}, {224, 64},
        {220, 32}, {176, 32}, {132, 32}, {88, 32}, {44, 32}, {0, 32}
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1,   1,  1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2
    }
};


void suspend_power_down_kb(void) {
 rgb_matrix_set_suspend_state(true);
 suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
 rgb_matrix_set_suspend_state(false);
 suspend_wakeup_init_user();
}
#endif

#if defined(ENCODER_ENABLE)
enum ENCODER_MODE {
    ENC_UP_DOWN = 0,
    ENC_VOLUME = 1,
    ENC_BRIGHTNESS = 2
};

typedef union {
    uint32_t raw;
    struct {
        char encoder_mode;
    };
} kb_config_t;

kb_config_t kb_config;

void keyboard_post_init_kb(void) {
  kb_config.raw = eeconfig_read_kb();
}

#define ENC_CODES_LEN 3
uint16_t ENC_CODES[ENC_CODES_LEN][2] = {
    { KC_DOWN,   KC_UP },
    { KC__VOLUP, KC__VOLDOWN },
    { KC_BRIU,   KC_BRID }
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_ENCT:
        if (record->event.pressed) {
            kb_config.encoder_mode = (kb_config.encoder_mode + 1) % ENC_CODES_LEN;
            eeconfig_update_kb(kb_config.raw);
        }
        return false;
    case KC_EXPO:
        if (record->event.pressed) {
            register_code(KC_APPLE_FN);
            tap_code(KC_F3);
            unregister_code(KC_APPLE_FN);
        }
        return false;
    case KC_LAUN:
        if (record->event.pressed) {
            register_code(KC_APPLE_FN);
            tap_code(KC_F4);
            unregister_code(KC_APPLE_FN);
        }
        return false;
    default:
        return true;
    }
}


bool encoder_update_kb(uint8_t index, bool clockwise) {
    if(encoder_update_user(index, clockwise)) {
        if(IS_LAYER_ON(_LOWER)) {
            #if defined(RGB_MATRIX_ENABLE)
            // Change RGB lightning effect if enabled
            if (rgb_matrix_is_enabled()) {
                clockwise ? rgb_matrix_step() : rgb_matrix_step_reverse();
            }
            #endif
        } else {
            uint16_t* keycodes = ENC_CODES[(int)kb_config.encoder_mode];

            if (clockwise) {
                tap_code(keycodes[0]);
            } else {
                tap_code(keycodes[1]);
            }
        }
        return true;
    }
    return false;
}
#endif
