#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

extern keymap_config_t keymap_config; 

// to compile: qmk compile -kb crkbd -km soundmonster

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _DVORAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _SINGLEHAND,
  _SINGLERIGHT
};

// Custom keycodes for layer keys
// Dual function escape with left command
#define KC_LGESC LGUI_T(KC_ESC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_RACL // right alt / colon
};

// dvorak // qwerty  Hola que Tal127,512,5126..567890177297838

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT(   //DVORAK NATIVO
  //,-----------------------------------------.                ,---------------------------------------------.
     KC_TAB,  KC_DOT,  KC_COMM,  KC_SCLN,  KC_P, KC_Y,            KC_F,  KC_G,  KC_C,  KC_H,  KC_L,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
   LCTL_T(KC_CAPS),  KC_A,  KC_O,  KC_E,  KC_U,  KC_I,                    KC_D,  KC_R,  KC_T,  KC_N, KC_S,KC_QUOT,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LALT,  KC_SLSH,  KC_Q,  KC_J,  KC_K,  KC_X,           KC_B,  KC_M,KC_W,KC_V,KC_Z,LSFT_T(KC_ENT),
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                               KC_LSFT,LOWER, KC_SPC,   KC_SPC, RAISE, KC_LCTL  //KC_LSFT    KC_LALT    KC_LCTL
                              //`--------------------'  `--------------------'
  ),
  [_QWERTY] = LAYOUT(  //SEGUNDA CAPA: QWERTY
    //,-----------------------------------------.                ,---------------------------------------------. 
      KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_BSPC,
    //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
      LCTL_T(KC_CAPS),  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                  KC_H,  KC_J,  KC_K,  KC_L, KC_SCLN,KC_QUOT,
    //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
      KC_LALT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,LSFT_T(KC_ENT),
    //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                               KC_LSFT,LOWER, KC_SPC,   KC_SPC, RAISE, KC_LSFT
                                //`--------------------'  `--------------------'
    ),

  
  [_SINGLEHAND] = LAYOUT(   //DVORAK SINGLEHAND   kjsdfljoaaasdfg 6456789123
  //,-----------------------------------------.                ,---------------------------------------------.
     KC_TAB,  KC_DOT,  KC_COMM,  KC_SCLN,  KC_P, KC_Y,            KC_F,  KC_G,  KC_C,  KC_H,  KC_L,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
   LCTL_T(KC_CAPS),  KC_A,  KC_O,  KC_E,  KC_U,  KC_I,                    KC_D,  KC_R,  KC_T,  KC_N, KC_S,KC_QUOT,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LALT,  KC_SLSH,  KC_Q,  KC_J,  KC_K,  KC_X,           KC_B,  KC_M,KC_W,KC_V,KC_Z,LSFT_T(KC_ENT),
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                               TG(_SINGLEHAND),MO(_SINGLERIGHT), KC_SPC,   KC_SPC, RAISE, KC_LCTL  
                              //`--------------------'  `--------------------'
  ),

  [_SINGLERIGHT] = LAYOUT(   // SINGLEHAND DERECHA    

  //,-----------------------------------------.                ,---------------------------------------------.
     KC_BSPC,  KC_L,  KC_H,  KC_C,  KC_G, KC_F,            KC_F,  KC_G,  KC_C,  KC_H,  KC_L,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
   KC_QUOT,  KC_S,  KC_N,  KC_T,  KC_R,  KC_D,                    KC_D,  KC_R,  KC_T,  KC_N, KC_S,KC_QUOT,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LCTL,  KC_Z,  KC_V,  KC_W,  KC_M,  KC_B,           KC_B,  KC_M,KC_W,KC_V,KC_Z,LSFT_T(KC_ENT),
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                               KC_TRNS,KC_TRNS, KC_SPC,   KC_SPC, RAISE, KC_LCTL  
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT(  //PULGAR IZQUIERDO (NUMEROS)
  //,---------------------------------------------.                ,-----------------------------------------.
     KC_ESC,  KC_DOT, KC_7,   KC_8,   KC_9,   KC_NO,                   KC_NO,  KC_NO,  KC_UP,  KC_NO,  KC_NO, KC_DEL,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_BSPC, KC_COMM, KC_4,   KC_5,   KC_6,   KC_0,                    KC_MPLY,KC_LEFT,KC_DOWN,KC_RIGHT,KC_MS_U,KC_BTN1,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_ENT, TG(_SINGLEHAND), KC_1, KC_2,  KC_3,  KC_BTN1,                    KC_NO, KC_NO, KC_BTN2, KC_MS_L,  KC_MS_D, KC_MS_R,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_TRNS, LOWER,KC_SPC,   KC_ENT, RAISE,KC_LGUI
                                  //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT(  //PULGAR DERECHO (SIMBOLOS)
  //,-----------------------------------------.                ,-----------------------------------------.
     ES_DLR,ES_COLN,ES_SCLN,ES_QUOT,ES_DQUO,ES_PERC,            ES_HASH,ES_LBRC,ES_RBRC,ES_IEXL,ES_EXLM,KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ES_EURO, ES_EQL, ES_LABK, ES_RABK, ES_SLSH, ES_BSLS,        ES_AMPR,ES_LPRN,ES_RPRN,ES_IQUE,ES_QUES,ES_GRV,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ES_DIAE, ES_UNDS, ES_PLUS, ES_ASTR, ES_CIRC,ES_AT,          ES_PIPE,ES_LCBR,ES_RCBR,ES_MORD,ES_FORD,ES_BULT,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LSFT, LOWER,KC_BSPC,   KC_SPC, RAISE,KC_NO
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
      QK_BOOT,RGBRST, KC_NO, KC_NO, KC_NO, TG(_QWERTY),                  KC_F1,KC_F2, KC_F3, KC_F4, KC_F5, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,TG(_ARROWS),             KC_F6,KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,KC_NO,             KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LSFT, LOWER,KC_SPC,   KC_SPC, RAISE,KC_LGUI
                              //`--------------------'  `--------------------'
  ),

  [_ARROWS] = LAYOUT(   ////FLECHAS PERMANENTES
    //,-----------------------------------------.                ,---------------------------------------------. 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                   KC_TRNS,  KC_TRNS,  KC_UP,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_TRNS,KC_TRNS,
    //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                               KC_TRNS,KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
                                //`--------------------'  `--------------------'
  )


};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}


void render_layer_name(void){
  oled_write_ln_P(PSTR("Mode:"), false);
  
  if(layer_state_is(_DVORAK)){  
      oled_write_ln_P(PSTR("Dvork"), false);
  }
  else if(layer_state_is(_QWERTY)){
      oled_write_ln_P(PSTR("QWERY"), false);
  }
  else if(layer_state_is(_SINGLEHAND)){
      oled_write_ln_P(PSTR("Left"), false);
      }
      //else {oled_write_ln_P(PSTR(""), false);}
  //if(layer_state_is(_ARROWS)){
   //   oled_write_ln_P(PSTR(""), false);
  //    }
    
  }





void render_info(void) {
  oled_write_ln_P(PSTR("Mode:"), false);
  switch(layer_state) {
    case 0:
      oled_write_ln_P(PSTR("0"), false);
      break;
    case 1:
      oled_write_ln_P(PSTR("1"), false);
      break;
    case 2:
      oled_write_ln_P(PSTR("2"), false);
      break;
    case 3:
      oled_write_ln_P(PSTR("3"), false);
      break;
    case 4:
      oled_write_ln_P(PSTR("4"), false);
      break;
    case 5:
      oled_write_ln_P(PSTR("5"), false);
      break;
    case 6:
      oled_write_ln_P(PSTR("6"), false);
      break;
    case 7:
      oled_write_ln_P(PSTR("7"), false);
      break;
    case 8:
      oled_write_ln_P(PSTR("8"), false);
      break;
    case 10:
      oled_write_ln_P(PSTR("10"), false);
      break;   
   case 12:
      oled_write_ln_P(PSTR("12"), false);
      break;   
  }
}

void render_text(void){
  oled_write_ln_P(PSTR("ARF  XYZZY"), false);
}
void render_line(void){
  oled_write_ln_P(PSTR("_____"), false);
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_triforce(void) {
    static const char PROGMEM triforce_image[] = {
        0x20, 0x20, 0x8a, 0x20, 0x20,
        0x20, 0x8b, 0x8c, 0x8d, 0x8e,
        0xaa, 0xab, 0xac, 0xad, 0x20,
        0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(triforce_image, false);
    //oled_write_P(PSTR("corne"), false);
}

void render_arrows(void){
  if(layer_state_is(_ARROWS)){
  static const char PROGMEM arrows_image[] = {
        0x85, 0x86, 0x87, 0x88, 0x89,
        0xa5, 0xa6, 0xa7, 0xa8, 0xa9,
        0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0};
    oled_write_P(arrows_image, false);
    //oled_write_P(PSTR("corne"), false);
  } else {
    static const char PROGMEM arrows_image[] = {
        0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0};
    oled_write_P(arrows_image, false);
  }
}

void render_layer(void) {
    static const char PROGMEM layer_image[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,       // 0x20   --- es BLANCO
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    oled_write_P(layer_image, false);
    //oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    //render_info();
    //render_line();
    render_layer_name();
    //render_line();
    //render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    //render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    //render_logo();
    //render_space();
    //render_layer_state();
    //render_space();
    render_text();
    render_space();
    //render_layer();
    render_triforce();
    render_space();
    render_arrows();
    //render_info();
    //render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    //render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }
  static uint16_t my_colon_timer;

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case KC_RACL:
        if (record->event.pressed) {
          my_colon_timer = timer_read();
          register_code(KC_RALT);
        } else {
          unregister_code(KC_RALT);
          if (timer_elapsed(my_colon_timer) < TAPPING_TERM) {
            SEND_STRING(":"); // Change the character(s) to be sent on tap here
          }
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
