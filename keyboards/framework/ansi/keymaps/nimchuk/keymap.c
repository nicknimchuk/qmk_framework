// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "framework.h"

#include "features/select_word.h"
#include "features/casemodes.h"

#include "secrets.h"

enum custom_keycodes {
    SELWORD = FW_SAFE_RANGE,    // Added feature
    RGT_PIP,                    // Quick |>
    CASEMDE,                    // Choose different case modes dependent on mods
    CASEMDEI,                   // CASEMDE with inverted shift
};

enum _layers {
  _COLEMAK_BASE,
  _QWERTY_BASE,
  _FN,
  _FN_LOCK,
  _FM,
  _NUMPAD,
  _SYM,
  _NAV,
  _SW_NAV,
};

#define _QB _QWERTY_BASE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │ESC  │Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Del │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \  │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift  │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │↑  │    │
     * 11 keys │Ctrl│FN │GUI│Alt│                   │Alt│Ctl│ ←  ├───┤  → │
     *         │    │   │   │   │                   │   │   │    │  ↓│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total
     */
    // Colemak bottom rows mods
    #define SFT_Z   LSFT_T(KC_Z)
    #define GUI_X   LGUI_T(KC_X)
    #define ALT_C   LALT_T(KC_C)
    #define CTL_D   LCTL_T(KC_D)
    #define SYM_G   LT(_SYM, KC_G)

    #define SYM_M   LT(_SYM, KC_M)
    #define CTL_H   RCTL_T(KC_H)
    #define ALT_CM  LALT_T(KC_COMM)
    #define GUI_DOT RGUI_T(KC_DOT)
    #define SFT_QT  RSFT_T(KC_QUOT)

    // Thumb key mods
    #define SNV_SPC LT(_SW_NAV, KC_SPC)
    #define NUM_DEL LT(_NUMPAD, KC_DEL)
    #define NAV_BS  LT(_NAV, KC_BSPC)
    #define SFT_ENT RSFT_T(KC_ENT)

    [_COLEMAK_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    KC_5,    KC_6,    KC_1,    KC_2,    KC_3,    KC_4,    XXXXXXX, XXXXXXX,
        CASEMDEI,KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    QK_LEAD, KC_J,    KC_L,    KC_U,    KC_Y,    KC_EXLM, CASEMDE, XXXXXXX,
        KC_UNDS, KC_A,    KC_R,    KC_S,    KC_T,    SYM_G,   XXXXXXX, SYM_M,   KC_N,    KC_E,    KC_I,    KC_O,             KC_MINS,
        SFT_Z,            GUI_X,   ALT_C,   CTL_D,   KC_V,    XXXXXXX, XXXXXXX, KC_K,    CTL_H,   ALT_CM,  GUI_DOT,          SFT_QT,
        XXXXXXX, MO(_FN), KC_TAB,  SNV_SPC,          NUM_DEL,                   NAV_BS,  SFT_ENT, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX
    ),
     /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │ESC  │Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Del │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \  │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift  │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │↑  │    │
     * 11 keys │Ctrl│FN │GUI│Alt│                   │Alt│Ctl│ ←  ├───┤  → │
     *         │    │   │   │   │                   │   │   │    │  ↓│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total
     */
    [_QWERTY_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT,          KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT
    ),
     /*
     * Function layer
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │FN lk│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Ins │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │   │   │   │   │   │   │   │   │   │   │   │   │   │      │
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │     │   │RGB│Nxt│Hue│Sat│Spd│Brt│   │   │Pau│   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │      │   │SRq│Prv│Hue│Sat│Spd│Brt│ScL│   │   │   │       │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │        │   │   │   │   │   │Brk│   │   │   │   │         │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     *         │    │   │   │   │                   │   │   │    │PgU│    │
     * 11 keys │    │   │   │   │ Toggle Backlight  │   │   │Home├───┤End │
     *         │    │   │   │   │                   │   │   │    │PgD│    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     * 78 total
     */
    [_FN] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_SPI, RGB_VAI, _______, _______, KC_PAUS, _______, _______, _______,
        TG(_QB), _______, KC_SYRQ, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, KC_SCRL, _______, _______, _______,          QK_BOOT,
        _______,          _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,          BL_STEP,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
    // Function lock layer
    // Everything on F-row locked to function layer, except ESC and DEL
    [_FN_LOCK] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, MO(_FM), _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
    // Locked+temporary FN (back to base plus extra keys)
    [_FM] = LAYOUT(
        FN_LOCK, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_SPI, RGB_VAI, _______, _______, KC_PAUS, _______, _______, _______,
        TG(_QB), _______, KC_SYRQ, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, KC_SCRL, _______, _______, _______,          QK_BOOT,
        _______,          _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,          BL_STEP,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
    /*
    // Layer template
    [_NAME] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
    */


    // Numpad bottom row mods
    #define GUI_F1  LGUI_T(KC_F1)
    #define ALT_F2  LALT_T(KC_F2)
    #define CTL_F3  LCTL_T(KC_F3)

    #define SYM_SPC LT(_SYM, KC_SPC)
    #define CTL_1   RCTL_T(KC_1)
    #define ALT_2   LALT_T(KC_2)
    #define GUI_3   RGUI_T(KC_3)
    #define SFT_PLS RSFT_T(KC_PLUS)     // User-processed

    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_DLR,  KC_LPRN, KC_PERC, KC_RPRN, _______, _______, _______,
        _______, _______, KC_F7,   KC_F8,   KC_F9,   _______, _______, KC_EQL,  KC_7,    KC_8,    KC_9,    KC_ASTR, _______, _______,
        _______, _______, KC_F4,   KC_F5,   KC_F6,   _______, _______, SYM_SPC, KC_4,    KC_5,    KC_6,    KC_SLSH,          _______,
        _______,          GUI_F1,  ALT_F2,  CTL_F3,  _______, _______, _______, KC_ENT,  CTL_1,   ALT_2,   GUI_3,            SFT_PLS,
        _______, _______, _______, _______,          _______,                   KC_0,    KC_DOT,  KC_COMM, _______, _______, _______
    ),

    // Sym bottom row mods
    #define SFT_GRV LSFT_T(KC_GRV)
    #define GUI_SLS LGUI_T(KC_SLSH)
    #define ALT_AST LALT_T(KC_ASTR)     // User-processed
    #define CTL_BSL LCTL_T(KC_BSLS)     // User-processed

    #define CTL_DOL RCTL_T(KC_DLR)      // User-processed
    #define ALT_LCB LALT_T(KC_LCBR)     // User-processed
    #define GUI_RCB RGUI_T(KC_RCBR)     // User-processed
    #define SFT_AT  RSFT_T(KC_AT)       // User-processed

    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F5,   KC_F6,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______,
        _______, _______, _______, KC_LABK, KC_RABK, _______, _______, KC_PIPE, KC_SCLN, KC_LBRC, KC_RBRC, KC_GRV,  _______, _______,
        _______, KC_CIRC, KC_MINS, KC_PLUS, KC_EQL,  KC_HASH, _______, KC_AMPR, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC,          _______,
        SFT_GRV,          GUI_SLS, ALT_AST, CTL_BSL, RGT_PIP, _______, _______, KC_TILD, CTL_DOL, ALT_LCB, GUI_RCB,          SFT_AT,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

    // Swapped Nav bottom row mods
    #define SFT_C_Z LSFT_T(KC_INT1)     // User-processed, overriden
    #define GUI_PGU LGUI_T(KC_PGUP)
    #define ALT_C_A LALT_T(C(KC_A))     // User-processed
    #define CTL_PGD LCTL_T(KC_PGDN)

    #define CTL_PRV RCTL_T(KC_MPRV)
    #define ALT_PLY LALT_T(KC_MPLY)
    #define GUI_NXT RGUI_T(KC_MNXT)
    #define SFT_MTE RSFT_T(KC_MUTE)

    #define G_GRV   LGUI(KC_GRV)
    #define C_HOME  LCTL(KC_HOME)
    #define C_END   LCTL(KC_END)
    #define C_LFT   LCTL(KC_LEFT)
    #define C_RGT   LCTL(KC_RGHT)
    #define A_F4    LALT(KC_F4)

    [_SW_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, G(KC_L), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, C_HOME,  KC_HOME, KC_UP,   KC_END,  C_END,   _______, _______, _______, A_F4,    _______, _______, _______, _______,
        G_GRV,   C_LFT,   KC_LEFT, KC_DOWN, KC_RGHT, C_RGT,   _______, _______, _______, _______, _______, _______,          _______,
        SFT_C_Z,          GUI_PGU, ALT_C_A, CTL_PGD, _______, _______, _______, _______, CTL_PRV, ALT_PLY, GUI_NXT,          SFT_MTE,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),


    // Nav bottom row mods
    //#define SFT_MTE RSFT_T(KC_MUTE)
    #define GUI_PRV LGUI_T(KC_MPRV)
    //#define ALT_PLY LALT_T(KC_MPLY)
    #define CTL_NXT LCTL_T(KC_MNXT)

    #define CTL_PGU RCTL_T(KC_PGUP)
    //#define ALT_C_A LALT_T(C(KC_A))     // User-processed
    #define GUI_PGD RGUI_T(KC_PGDN)
    //#define SFT_C_Z LSFT_T(KC_INT1)     // User-processed, overriden

    //#define G_GRV   LGUI(KC_GRV)
    //#define C_HOME  LCTL(KC_HOME)
    //#define C_END   LCTL(KC_END)
    //#define C_LFT   LCTL(KC_LEFT)
    //#define C_RGT   LCTL(KC_RGHT)
    //#define A_F4    LALT(KC_F4)

    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, G(KC_L), _______, _______, _______, _______,
        _______, _______, _______, A_F4,    _______, _______, _______, C_HOME,  KC_HOME, KC_UP,   KC_END,  C_END,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, C_LFT,   KC_LEFT, KC_DOWN, KC_RGHT, C_RGT,            G_GRV,
        SFT_MTE,          GUI_PRV, ALT_PLY, CTL_NXT, _______, _______, _______, _______, CTL_PGU, ALT_C_A, GUI_PGD,          SFT_C_Z,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),

};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    if (!process_case_modes(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    switch (keycode) {
        case FN_LOCK:
            // Make sure to keep FN Lock even after reset
            if (record->event.pressed) {
                if (layer_state_is(_FN)) {
                    set_single_persistent_default_layer(_FN_LOCK);
                }
                if (layer_state_is(_FM)) {
                    set_single_persistent_default_layer(_COLEMAK_BASE);
                }
            }
            return false;
            break;

        // Macros
        case RGT_PIP:
            if (record->event.pressed) {
                SEND_STRING("|>");

                return false;
            }
            break;


        case CASEMDE:
            if (record->event.pressed) {
                clear_mods();  // Temporarily disable mods.
                clear_oneshot_mods();

                if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                    enable_xcase_with(OSM(MOD_LSFT));
                } else {
                    enable_xcase();
                }

                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                    enable_caps_word();
                }

                set_mods(mods);  // Restore mods.
                return false;
            }
            break;

        case CASEMDEI:
            if (record->event.pressed) {
                clear_mods();  // Temporarily disable mods.
                clear_oneshot_mods();

                if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                    enable_xcase_with(OSM(MOD_LSFT));
                } else {
                    enable_xcase();
                }

                if (!((mods | oneshot_mods) & MOD_MASK_SHIFT)) {
                    enable_caps_word();
                }

                set_mods(mods);  // Restore mods.
                return false;
            }
            break;


        // Tap/hold user-processed

        case SFT_PLS:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_PLUS);
                return false;
            }
            break;

        case ALT_AST:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_ASTR);
                return false;
            }
            break;

        case CTL_BSL:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_BSLS);
                return false;
            }
            break;

        case CTL_DOL:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DLR);
                return false;
            }
            break;

        case ALT_LCB:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);
                return false;
            }
            break;

        case GUI_RCB:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR);
                return false;
            }
            break;

        case SFT_AT:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_AT);
                return false;
            }
            break;

        case SFT_C_Z:
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_Z));
                return false;
            }
            break;

        case ALT_C_A:
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_A));
                return false;
            }
            break;

        // Custom shifted keys

        case KC_EXLM:
            if (record->event.pressed &&
                    ((mods | oneshot_mods) & MOD_MASK_SHIFT)) {

                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);

                tap_code16(KC_QUES);

                set_mods(mods);
                return false;
            }
            break;

        case ALT_CM:
            if (record->tap.count && record->event.pressed &&
                    ((mods | oneshot_mods) & MOD_MASK_SHIFT)) {

                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);

                tap_code16(KC_SLSH);

                set_mods(mods);
                return false;
            }
            break;

        case GUI_DOT:
            if (record->tap.count && record->event.pressed &&
                    ((mods | oneshot_mods) & MOD_MASK_SHIFT)) {

                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);

                tap_code16(KC_BSLS);

                set_mods(mods);
                return false;
            }
            break;


        default:
            break;
    }
    return true;
}



bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_SPC:
            return true;
    }
    return false;
}


bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUM_DEL:
        case NAV_BS:
        case SFT_ENT:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUM_DEL:
        case NAV_BS:
        case GUI_PGD:
        case CTL_PGU:
        case CTL_PGD:
        case GUI_PGU:
        case SFT_C_Z:
            return false;
        default:
            return true;
    }
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SFT_Z:
        case GUI_X:
        case ALT_C:
        case CTL_D:
        case SYM_G:
        case SYM_M:
        case CTL_H:
        case ALT_CM:
        case GUI_DOT:
        case KC_EXLM:
        case SFT_QT:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case ALT_CM:
            register_code16(((!shifted) ? KC_COMM : KC_SLSH) & 0xFF);
            break;
        case GUI_DOT:
            register_code16(((!shifted) ? KC_DOT : KC_BSLS) & 0xFF);
            break;
        case KC_EXLM:
            register_code16((!shifted) ? KC_EXLM : KC_QUES);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case ALT_CM:
            unregister_code16(((!shifted) ? KC_COMM : KC_SLSH) & 0xFF);
            break;
        case GUI_DOT:
            unregister_code16(((!shifted) ? KC_DOT : KC_BSLS) & 0xFF);
            break;
        case KC_EXLM:
            unregister_code16((!shifted) ? KC_EXLM : KC_QUES);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_W)) {
        SEND_STRING(SECRET_WMAIL);

    } else if (leader_sequence_one_key(KC_R)) {
        SEND_STRING(SECRET_REGRD);

    } else if (leader_sequence_one_key(KC_M)) {
        SEND_STRING("| more");

    } else if (leader_sequence_one_key(KC_L)) {
        SEND_STRING("| less");

    } else if (leader_sequence_one_key(KC_H)) {
        SEND_STRING(SECRET_HMAIL);

    } else if (leader_sequence_two_keys(KC_A, KC_R)) {
        SEND_STRING(SECRET_ADSTR);

    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        SEND_STRING(SECRET_ADCIT);

    } else if (leader_sequence_two_keys(KC_A, KC_T)) {
        SEND_STRING(SECRET_ADZIP);

    } else if (leader_sequence_one_key(KC_N)) {
        SEND_STRING(SECRET_NAMES);

    } else if (leader_sequence_two_keys(KC_N, KC_N)) {
        SEND_STRING(SECRET_NAMEL);
    }
}
