#include QMK_KEYBOARD_H

#define MATRIX_ROWS 4
#define MATRIX_COLS 2

enum custom_keycodes {
  SW3_INTERVAL = SAFE_RANGE,
  SW4_Round  
};

static uint8_t current_interval = 1;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ENT, SW3_INTERVAL,                //SW1 Enter, SW3 bytt intervall
        LCA(KC_E), LCA(KC_C),           //SW2 extrude boss base (Crl-alt-e), SW5 cut extruded part (ctrl-alt-c)
        LCA(KC_P), KC_S,             //SW6 chose plane, SW7 sketch
        SW4_Round,  KC_NO     
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

        case SW3_INTERVAL:
            if(current_interval == 1) {
                current_interval = 10;
            } else if (current_interval == 10) {
                current_interval = 25;
            } else {
                current_interval = 1;
            }
            return false; 

        case SW4_Round:                                              //Writing the many commands beforehand ctrl+a ctrl+x mark and cut
            SEND_STRING(SS_DOWN(X_LCTRL) "ax" SS_UP(X_LCTRL));       //round(x/10)*10 (if you need to round a number your not in the 0.1,s)
            SEND_STRING("=round(");
            SEND_STRING(SS_DOWN(X_LCTRL) "v" SS_UP(X_LCTRL));
            SEND_STRING("/10)*10" SS_TAP(X_ENT));

            return false;

        }
    }
    return true;
}

            
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        
        for (uint8_t i = 0; i < current_interval; i++) {
            if (clockwise) {
                tap_code(KC_UP);  // with the clock, up
            } else {
                tap_code(KC_DOWN); // against the clock, down
            }
        }
    }
    return true;
}