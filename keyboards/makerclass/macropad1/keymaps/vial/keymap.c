// Copyright 2025 MakerClass (@makerclass)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Conditional compilation for layout support
// Compile with: qmk compile -kb makerclass/macropad1 -km vial -e USE_CZECH_LAYOUT=yes
#ifdef USE_CZECH_LAYOUT
    #include "keymap_czech.h"
    #include "sendstring_czech.h"
    #define NOTEPAD_TEXT "Ahoj z MakerClass!"
#else
    #define NOTEPAD_TEXT "Hello from MakerClass!"
#endif

// Custom keycodes pro makra
enum custom_keycodes {
    M_MEDIAPLAYER = SAFE_RANGE,  // Otevřít media player
    M_NOTEPAD,                    // Win+R -> notepad -> text
};

// Definice vrstev
enum layers {
    _BASE = 0,    // Vrstva 1 - Zakladni navigace - Cyan
    _MEDIA,       // Vrstva 2 - Media ovladani - Green
    _MACROS,      // Vrstva 3 - Makra - Magenta
    _TYPE,        // Vrstva 4 - Psani - Yellow
    _UTILS,       // Vrstva 5 - Nastaveni - Red
    _LAYER_SWITCH // Pomocna vrstva pro prepinani
};

// Keymap - 7 tlacitek (6 hlavnich + encoder switch)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Vrstva 1: BASE - Zakladni navigace
     * LED: Cyan 🔵
     * ┌─────┬─────┬───────────┬─────┬─────┬──────┬──────┐
     * │SPACE│ UP  │ENTER/LAYER│LEFT │DOWN │RIGHT │ MUTE │
     * └─────┴─────┴───────────┴─────┴─────┴──────┴──────┘
     * ENC: Volume +/-
     */
    [_BASE] = LAYOUT(
        KC_SPC,  KC_UP,  LT(_LAYER_SWITCH, KC_ENT),  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_MUTE
    ),

    /*
     * Vrstva 2: MEDIA - Media ovladani
     * LED: Green 🟢
     * ┌──────┬─────┬──────────┬─────┬──────┬─────┬──────┐
     * │PLAYER│STOP │---/LAYER │PREV │PLAY  │NEXT │ MUTE │
     * └──────┴─────┴──────────┴─────┴──────┴─────┴──────┘
     * ENC: Volume +/-
     * Poznámka: KC_MREC není standardní keycode, ponecháno prázdné
     */
    [_MEDIA] = LAYOUT(
        M_MEDIAPLAYER,  KC_MSTP,  LT(_LAYER_SWITCH, KC_NO),  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE
    ),

    /*
     * Vrstva 3: MACROS - Makra
     * LED: Magenta 🟣
     * ┌──────┬──────┬──────────┬──────┬──────┬────────┬──────┐
     * │ALT TAB│CTRL C│PSCR/LAYER│CTRL D│CTRL V│NOTEPAD │ MUTE │
     * └──────┴──────┴──────────┴──────┴──────┴────────┴──────┘
     * ENC: Volume +/-
     */
    [_MACROS] = LAYOUT(
        LALT(KC_TAB),  C(KC_C),  LT(_LAYER_SWITCH, KC_PSCR),  C(KC_D),  C(KC_V),  M_NOTEPAD,  KC_MUTE
    ),

    /*
     * Vrstva 4: TYPE - Psani maker/s
     * LED: Yellow 🟡
     * ┌───┬───┬─────────┬───┬───┬───┬─────────┐
     * │ M │ A │ K/LAYER │ E │ R │ S │RGB TOGG │
     * └───┴───┴─────────┴───┴───┴───┴─────────┘
     * ENC: RGB Hue +/-
     */
    [_TYPE] = LAYOUT(
        KC_M,  KC_A,  LT(_LAYER_SWITCH, KC_K),  KC_E,  KC_R,  KC_S,  RGB_TOG
    ),

    /*
     * Vrstva 5: UTILS - Nastaveni a QMK funkce
     * LED: Red 🔴
     * ┌────────┬──────┬──────────┬────────┬──────────┬──────┬─────────┐
     * │RGB MODE│DEBUG │---/LAYER │RGB TOGG│BOOTLOADER│EE CLR│RGB TOGG │
     * └────────┴──────┴──────────┴────────┴──────────┴──────┴─────────┘
     * ENC: RGB Brightness +/-
     */
    [_UTILS] = LAYOUT(
        RGB_MOD,  DB_TOGG,  LT(_LAYER_SWITCH, KC_NO),  RGB_TOG,  QK_BOOT,  EE_CLR,  RGB_TOG
    ),

    /*
     * LAYER_SWITCH vrstva - Pomocna pro prepinani vrstev
     * Drž tlačítko 3 a stiskni:
     * ┌──────┬───────┬─────┬────────┬──────┬───────┬─────┐
     * │->L1  │->L2   │ --- │->L3    │->L4  │->L5   │ --- │
     * └──────┴───────┴─────┴────────┴──────┴───────┴─────┘
     *  BASE   MEDIA         MACROS   TYPE   UTILS
     */
    [_LAYER_SWITCH] = LAYOUT(
        TO(_BASE),  TO(_MEDIA),  KC_NO,  TO(_MACROS),  TO(_TYPE),  TO(_UTILS),  KC_NO
    )
};

// Encoder mapping pro jednotlive vrstvy
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]         = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },  // Volume Down/Up
    [_MEDIA]        = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },  // Volume Down/Up
    [_MACROS]       = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },  // Volume Down/Up
    [_TYPE]         = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },  // RGB Hue Down/Up
    [_UTILS]        = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },  // RGB Brightness Down/Up
    [_LAYER_SWITCH] = { ENCODER_CCW_CW(KC_NO,   KC_NO)   }   // No function while switching
};
#endif

// RGB layers - indikace vrstev pomoci barev s fixnim nizkym jasem
#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM layer_base_rgb[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, 128, 255, 96});  // Cyan
const rgblight_segment_t PROGMEM layer_media_rgb[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, 85, 255, 96});   // Green
const rgblight_segment_t PROGMEM layer_macros_rgb[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, 213, 255, 96});  // Magenta
const rgblight_segment_t PROGMEM layer_type_rgb[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, 43, 255, 96});   // Yellow
const rgblight_segment_t PROGMEM layer_utils_rgb[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, 0, 255, 96});    // Red
const rgblight_segment_t PROGMEM layer_switch_rgb[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, 0, 0, 128});      // White

// Pole RGB layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_base_rgb,
    layer_media_rgb,
    layer_macros_rgb,
    layer_type_rgb,
    layer_utils_rgb,
    layer_switch_rgb
);

// Aktivace RGB layer podle aktivni vrstvy
// Pouze pokud je RGB mode nastavený na STATIC_LIGHT (mode 1)
layer_state_t layer_state_set_user(layer_state_t state) {
    // Layer indikace funguje pouze v STATIC_LIGHT mode
    if (rgblight_get_mode() == 1) {
        rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
        rgblight_set_layer_state(1, layer_state_cmp(state, _MEDIA));
        rgblight_set_layer_state(2, layer_state_cmp(state, _MACROS));
        rgblight_set_layer_state(3, layer_state_cmp(state, _TYPE));
        rgblight_set_layer_state(4, layer_state_cmp(state, _UTILS));
        rgblight_set_layer_state(5, layer_state_cmp(state, _LAYER_SWITCH));
    }
    return state;
}

// Inicializace pri startu
void keyboard_post_init_user(void) {
    // Nastavit RGB layers pro automatickou indikaci vrstev
    rgblight_layers = my_rgb_layers;

    // Zapnout RGB
    rgblight_enable();

    // Nastavit static light mode (bez animaci) pro cistou layer indikaci
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);

    // Barva bude automaticky nastavena podle aktivni vrstvy
    // pres layer_state_set_user() - nyni BASE (Cyan)
}
#endif

// Zpracovani vlastnich makra
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Reagujeme pouze na stisk (press), ne na uvolneni (release)
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case M_MEDIAPLAYER:
            // Otevřít media player: Win+R -> ms-media-player:
            SEND_STRING(SS_LGUI("r"));           // Win+R
            wait_ms(200);
            SEND_STRING("ms-media-player:");     // Protocol handler
            wait_ms(100);
            SEND_STRING(SS_TAP(X_ENTER));        // Enter
            return false;

        case M_NOTEPAD:
            // Makro: Win+R -> notepad -> Enter -> text
            SEND_STRING(SS_LGUI("r"));           // Win+R
            wait_ms(200);
            SEND_STRING("notepad");              // Napsat "notepad"
            wait_ms(100);
            SEND_STRING(SS_TAP(X_ENTER));        // Enter
            wait_ms(300);
            SEND_STRING(NOTEPAD_TEXT);           // Text do notepadku (CZ/EN based on compile flag)
            return false;

        case RGB_MOD:
            // Když měníme RGB mode, vypneme RGB layer indikaci
            // aby uživatel mohl používat vlastní barvy/animace
            rgblight_set_layer_state(0, false);
            rgblight_set_layer_state(1, false);
            rgblight_set_layer_state(2, false);
            rgblight_set_layer_state(3, false);
            rgblight_set_layer_state(4, false);
            rgblight_set_layer_state(5, false);
            return true;  // Pokračovat normálním zpracováním RGB_MOD
    }

    return true;
}
