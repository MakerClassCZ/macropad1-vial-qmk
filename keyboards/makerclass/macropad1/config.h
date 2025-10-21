// Copyright 2025 MakerClass (@makerclass)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Debounce snižuje chatterbounce (5ms je dobrá výchozí hodnota)
#define DEBOUNCE 5

// USB polling interval - 1ms pro rychlejší odezvu
#define USB_POLLING_INTERVAL_MS 1

// Encoder nastavení
#define ENCODER_RESOLUTION 4
#define ENCODER_DEFAULT_POS 0x3

// RGB LED konfigurace
// WS2812_DI_PIN a RGBLED_NUM jsou definované v keyboard.json
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_DEFAULT_VAL 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

// RGBLIGHT_LAYERS je definován v keyboard.json jako rgblight.layers.enabled
// Layer indikace je aktivní pouze když je RGB zapnuté
#define RGBLIGHT_MAX_LAYERS 8

// RP2040 specifické nastavení
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U

// Vial configuration
// VIA/Vial layer count (musí odpovídat počtu vrstev v keymap.c)
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Vial combo a tap dance entries (pokud použiješ)
#define VIAL_COMBO_ENTRIES 8
#define VIAL_TAP_DANCE_ENTRIES 8