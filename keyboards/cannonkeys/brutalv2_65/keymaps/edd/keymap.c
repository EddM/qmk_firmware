#include QMK_KEYBOARD_H

enum layer_names {
  _BASE,
  _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_all(
		KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  LSG(KC_A),
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_PGUP,
		KC_ESCAPE,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(_FN),
		KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RALT,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN] = LAYOUT_all(
		QK_BOOT, KC_F14,   KC_F15,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DELETE, _______, _______,
		_______, _______, _______, KC_PGUP, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______,          _______, _______,
		_______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, _______,
		_______, _______, _______,                            _______,                            _______, _______,          KC_HOME, KC_PGDN, KC_END
  )
};

void capslock_led_on(void) {
  // B3 PIN is capslock LED, see keyboard.json
  gpio_write_pin_low(B3); // counter-intuitively, setting pin to low is 'on'
}

void capslock_led_off(void) {
  gpio_write_pin_high(B3);
}

void keyboard_post_init_user(void) {
  capslock_led_on();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (res) {
        if (!led_state.caps_lock) {
            capslock_led_on();
        }
    }

    return res;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_ESC:
      if (record->event.pressed) {
        capslock_led_off();
      } else {
        capslock_led_on();
      }

      return true;
    default:
      return true;
  }
}
