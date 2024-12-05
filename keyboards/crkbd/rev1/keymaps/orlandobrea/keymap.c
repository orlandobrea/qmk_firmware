/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

// static uint32_t oled_timer = 0;

#define BS_LOW LT(_LOWER, KC_BSPC)
#define ENT_RAISE LT(_RAISE, KC_ENT)
#define ESC_CTL LCTL_T(KC_ESC)
#define ENT_SHFT LSFT_T(KC_ENT)
#define GRV_NUM  LT(_NUMBERS, KC_GRV)
#define CTL_SPC RCTL_T(KC_SPC)
#define SFT_SPC LSFT_T(KC_SPC)
#define ALT_ESC LALT_T(KC_ESC)
#define HYP_CAPS HYPR_T(KC_CAPS)
#define TMUX RCTL(KC_B)
#define UNDO G(KC_Z)
#define REDO SCMD(KC_Z)
#define MIC_TGL RAG(KC_F1)
#define VOL_UP KC_KB_VOLUME_UP
#define VOL_DW KC_KB_VOLUME_DOWN
#define VOL_MUTE KC_KB_MUTE

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMBERS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_split_3x6_3( \
  //,------------------------------------------------------.    ,-----------------------------------------------------------------.
     KC_ESC,   KC_SCLN , KC_COMM , KC_DOT , KC_P   , KC_Y   ,        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,\
  //|--------+---------+---------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
     GRV_NUM,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
     HYP_CAPS, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RALT_T(KC_DLR),\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
            RGUI_T(KC_BSPC), LT(_LOWER, KC_TAB), CTL_SPC,        SFT_SPC, ENT_RAISE, LALT_T(KC_ESC) \
  //       `---------------------------------------------'      `---------------------------------------------'
  ),


  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.    ,-----------------------------------------------------------------.
     QK_BOOTLOADER, _______, KC_LT,  KC_GT,  _______, KC_LCBR,           KC_RCBR, KC_PGUP, KC_UP,   _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
     _______,   UNDO  ,  REDO  , MS_BTN2, MIC_TGL, KC_LPRN,          KC_RPRN, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
     _______, G(KC_A), G(KC_C), G(KC_V), G(KC_X), KC_LBRC,         KC_RBRC, KC_PGDN, _______, KC_HOME, KC_END, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+-------------------|
                                _______, _______, _______,        _______, _______, _______ \
                             //`----------XXXXX----------'  `----------------------'

  ),

  // 

  [_RAISE] = LAYOUT_split_3x6_3( \
    KC_TILD , KC_EXLM   , KC_AT      , KC_HASH   , KC_DLR    , KC_PERC ,       KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSLS , \
    _______ , TMUX      , LALT(KC_1) , LALT(KC_2), LALT(KC_3), LALT(KC_4),     KC_MINS , KC_EQL  , KC_BSLS , KC_LBRC , KC_RBRC , KC_MINS , \
    _______ , LALT(KC_5), LALT(KC_6) , LALT(KC_7), LALT(KC_8), LALT(KC_9),     KC_LT   , KC_GT   , KC_PIPE , KC_LCBR , KC_RCBR , _______ , \
                                            _______,_______,_______,            _______ ,_______,_______ \
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
     QK_BOOTLOADER   ,  _______ ,  VOL_UP ,  KC_MNXT ,  _______ ,  KC_BRIU ,           KC_F13 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10 ,  _______ ,\
     KC_WAKE ,  _______ ,  VOL_MUTE ,  KC_MPLY ,  _______ ,  _______ ,           KC_F14 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F11 ,  _______ ,\
     _______ ,  _______ ,  VOL_DW ,  KC_MPRV ,  _______ ,  KC_BRID ,           KC_F15 ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F12 ,  _______ ,\
                                            _______,_______,_______,            _______ ,_______,_______ \
  ),

[_NUMBERS] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------.          ,-----------------------------------------------.
     _______,_______,KC_TILD,KC_EXLM,KC_AT,_______,            KC_PSLS,KC_7,KC_8,KC_9,KC_PPLS,S(KC_SCLN),\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,_______,KC_HASH,KC_DLR,KC_PERC,_______,           KC_ASTR,KC_4,KC_5,KC_6,KC_PMNS,KC_EQL,\
  //|--XXXX-+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,_______,KC_CIRC,KC_AMPR,KC_ASTR,_______,           KC_DOT,KC_1,KC_2,KC_3,KC_0,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                _______,_______,_______,   _______ ,_______,_______ \
                             //`-----------------------'  `----------------------'
  )

};
int RGB_current_mode;

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
// Setting ADJUST layer RGB back to default
/* void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) { */
/*   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) { */
/*     layer_on(layer3); */
/*   } else { */
/*     layer_off(layer3); */
/*   } */
/* } */
void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init();   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; } */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}



char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

  char name = ' ';
  void set_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}


void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}

char matrix_line_str[24];

const char *read_layer_state(void) {
  uint8_t layer = biton32(layer_state);

  oled_write_P(PSTR("Layer: "), false);
  switch (layer)
  {
    case _DVORAK:
      oled_write_ln_P(PSTR("DVORAK"), false);
      break;
    case _LOWER:
      oled_write_ln_P(PSTR("LOWER"), false);
      break;
    case _RAISE:
      oled_write_ln_P(PSTR("RAISE"), false);
      break;
    case _NUMBERS:
      oled_write_ln_P(PSTR("NUM"), false);
      break;
    case _ADJUST:
      oled_write_ln_P(PSTR("ADJ"), false);
      break;
    default:
      oled_write_ln_P(PSTR("UNKNOWN"), false);
  }

  return matrix_line_str;
}

void read_usb_state(void) {
  oled_write_ln_P(PSTR("USB"), false);
  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      oled_write_ln_P(PSTR("Unattached"), false);
      break;
    case DEVICE_STATE_Suspended:
      oled_write_ln_P(PSTR("Suspended"), false);
      break;
    case DEVICE_STATE_Configured:
      oled_write_ln_P(PSTR("Connected"), false);
      break;
    case DEVICE_STATE_Powered:
      oled_write_ln_P(PSTR("Powered"), false);
      break;
    case DEVICE_STATE_Default:
      oled_write_ln_P(PSTR("Default"), false);
      break;
    case DEVICE_STATE_Addressed:
      oled_write_ln_P(PSTR("Addressed"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Invalid"), false);
  }

}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  oled_on();
  if (is_keyboard_master()) {
    oled_write_ln_P(PSTR("Default"), false);
    read_layer_state();
    read_usb_state();
    oled_render_keylog();
  } else {
    oled_render_logo();
  }
  return false;
}
#endif
