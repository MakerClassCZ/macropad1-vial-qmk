# MakerClass Macropad 1

Port [QMK firmware](https://github.com/vial-kb/vial-qmk) s VIAL podporou pro Makerclass macropad s 6 tlačítky, rotačním enkodérem a RGB LED indikací.

## Hardware

- **Mikrokontrolér**: Raspberry Pi Pico (RP2040)
- **Tlačítka**: 6 hlavních + 1 encoder switch
- **Encoder**: Rotační enkodér s tlačítkem
- **RGB LED**: 1× WS2812 RGB LED pro indikaci vrstev

## Vrstvy

Macropad má 5 hlavních vrstev s barevnou indikací:

### Vrstva 1: BASE - Základní navigace 🔵
**Barva LED**: Cyan (azurová)

| Tlačítko | Funkce |
|----------|--------|
| 1 | Space |
| 2 | Šipka nahoru |
| 3 | Enter (HOLD = přepínání vrstev) |
| 4 | Šipka vlevo |
| 5 | Šipka dolů |
| 6 | Šipka vpravo |
| 7 | Mute (ztlumení) |
| **Encoder** | Hlasitost +/- |

### Vrstva 2: MEDIA - Ovládání médií 🟢
**Barva LED**: Green (zelená)

| Tlačítko | Funkce |
|----------|--------|
| 1 | Otevřít Media Player |
| 2 | Stop |
| 3 | --- (HOLD = přepínání vrstev) |
| 4 | Předchozí skladba |
| 5 | Play/Pause |
| 6 | Další skladba |
| 7 | Mute |
| **Encoder** | Hlasitost +/- |

### Vrstva 3: MACROS - Makra a zkratky 🟣
**Barva LED**: Magenta (fialová)

| Tlačítko | Funkce |
|----------|--------|
| 1 | Alt+Tab |
| 2 | Ctrl+C (kopírovat) |
| 3 | Print Screen (HOLD = přepínání vrstev) |
| 4 | Ctrl+D |
| 5 | Ctrl+V (vložit) |
| 6 | Notepad makro* |
| 7 | Mute |
| **Encoder** | Hlasitost +/- |

*Notepad makro: Otevře Notepad a napíše "Ahoj z MakerClass!" (CZ verze) / "Hello from MakerClass!" (EN verze)

### Vrstva 4: TYPE - Psaní textu 🟡
**Barva LED**: Yellow (žlutá)

| Tlačítko | Funkce |
|----------|--------|
| 1 | M |
| 2 | A |
| 3 | K (HOLD = přepínání vrstev) |
| 4 | E |
| 5 | R |
| 6 | S |
| 7 | RGB Toggle (zap/vyp RGB) |
| **Encoder** | RGB Hue (změna barvy) |

### Vrstva 5: UTILS - Nastavení 🔴
**Barva LED**: Red (červená)

| Tlačítko | Funkce |
|----------|--------|
| 1 | RGB Mode (přepínání efektů) |
| 2 | Debug Toggle |
| 3 | --- (HOLD = přepínání vrstev) |
| 4 | RGB Toggle (zap/vyp RGB) |
| 5 | Bootloader (pro nahrání firmware) |
| 6 | EEPROM Clear (reset nastavení) |
| 7 | RGB Toggle (zap/vyp RGB) |
| **Encoder** | RGB Brightness (jas) |

## Přepínání vrstev

1. **Držte tlačítko 3**
2. **Zmáčkněte tlačítko pro přepnutí**:
   - Tlačítko 1 → BASE (Cyan)
   - Tlačítko 2 → MEDIA (Green)
   - Tlačítko 4 → MACROS (Magenta)
   - Tlačítko 5 → TYPE (Yellow)
   - Tlačítko 6 → UTILS (Red)
3. **Pusťte tlačítko 3**

RGB LED se změní na barvu aktivní vrstvy.

## RGB LED ovládání

### Layer indikace (výchozí)
- RGB LED automaticky ukazuje barvu aktivní vrstvy

### Vlastní barvy a animace
1. **Zmáčkněte RGB_MOD** (UTILS vrstva, tlačítko 1)
2. Layer indikace se vypne
3. Můžete nastavit vlastní barvy a efekty přes:
   - **Vial aplikaci** (záložka Lighting)
   - **RGB_MOD** - přepíná efekty (Breathing, Rainbow, Snake, atd.)
   - **Encoder** na TYPE vrstvě - mění barvu
   - **Encoder** na UTILS vrstvě - mění jas

### Návrat k layer indikaci
- Zmáčkejte **RGB_MOD** opakovaně, dokud se nevrátíte na **Static Light** mode
- Při další změně vrstvy se layer indikace znovu zapne

## Vial konfigurace

Firmware podporuje **Vial** - grafické rozhraní pro konfiguraci klávesnice v reálném čase.

1. Nahrajte firmware do macropadu
2. Otevřete https://vial.rocks v prohlížeči
3. Připojte macropad
4. Můžete měnit:
   - Funkce tlačítek
   - Encoder mapování pro každou vrstvu
   - RGB efekty a barvy
   - Makra, Combos, Tap Dance
   - QMK nastavení

**Poznámka**: Custom makra (Media Player, Notepad) jsou zobrazena jako "Media Player" a "Notepad Macro" v sekci User keycodes.

## Kompilace firmware

### Česká verze (QWERTZ layout)
```bash
qmk compile -kb makerclass/macropad1 -km vial -e USE_CZECH_LAYOUT=yes
```
Výstup: `makerclass_macropad1_vial.uf2`

### Anglická verze (US layout)
```bash
qmk compile -kb makerclass/macropad1 -km vial
```
Výstup: `makerclass_macropad1_vial.uf2`

## Nahrání firmware

1. **Odpojte macropad** od USB
2. **Držte tlačítko BOOTSEL** na Raspberry Pi Pico
3. **Připojte USB** (stále držte BOOTSEL)
4. **Pusťte BOOTSEL** - Pico se připojí jako USB disk
5. **Přetáhněte `.uf2` soubor** na disk
6. Pico se automaticky restartuje s novým firmware

**Alternativně** (po nahrání Vial firmware):
- Přejděte na UTILS vrstvu
- Zmáčkněte tlačítko 5 (QK_BOOT)
- Pico přejde do bootloader módu

## Technické detaily

- **Firmware**: QMK s Vial podporou
- **VIA protocol**: 9
- **Vial protocol**: 6
- **Encoder resolution**: 4
- **USB polling**: 1ms
- **Debounce**: 5ms
- **RGB LED jas (layer indikace)**: 96/255 (38%)

## Soubory

- `keyboard.json` - Definice hardware (piny, matrix, encoder, RGB)
- `config.h` - Konfigurace firmware (debounce, encoder, RGB nastavení)
- `rules.mk` - Build pravidla
- `keymaps/vial/keymap.c` - Definice vrstev a maker (s podmíněnou kompilací CZ/EN)
- `keymaps/vial/vial.json` - Layout pro Vial aplikaci
- `keymaps/vial/config.h` - Vial UID a nastavení

## Autor

Vladimír Smitka (@MakerClassCZ)
Licence: GPL-2.0-or-later
