/* -*- mode: c++ -*-
 * Kaleidoscope - A Kaleidoscope example
 * Copyright (C) 2016-2019  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define DEBUG_SERIAL false

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LED-ActiveModColor.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope.h"

#include "Kaleidoscope-Qukeys.h"

#define NUMPAD_KEYMAP 2

#define MACRO_CC 1
#define MACRO_CX 2
#define MACRO_CH 3
#define MACRO_CG 4

#define GENERIC_FN2                                                            \
  KEYMAP_STACKED(                                                              \
      ___, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, XXX, Key_Tab,               \
      Key_mouseBtnM, Key_mouseUp, ___, Key_mouseWarpNW, Key_mouseWarpNE,       \
      Consumer_ScanNextTrack, Key_Home, Key_mouseL, Key_mouseDn, Key_mouseR,   \
      Key_mouseWarpSW, Key_mouseWarpSE, Key_End, Key_Z, Key_X, Key_C, Key_V,   \
      Key_mouseWarpEnd, ___, Key_LeftControl, Key_mouseBtnL, Key_LeftGui,      \
      Key_LeftShift, ___,                                                      \
                                                                               \
      Key_mouseScrollUp, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_KeypadNumLock, Key_mouseScrollDn, \
      Consumer_PlaySlashPause, Key_LeftCurlyBracket, Key_RightCurlyBracket,    \
      Key_LeftBracket, Key_RightBracket, System_Sleep, Key_LeftArrow,          \
      Key_DownArrow, Key_UpArrow, Key_RightArrow, Key_F11, Key_F12, ___,       \
      Consumer_VolumeDecrement, Consumer_VolumeIncrement, Key_BacklightDown,   \
      Key_BacklightUp, Key_Backslash, Key_Pipe, Key_RightShift, Key_RightAlt,  \
      Key_mouseBtnR, Key_RightControl, ___)

#define NUMPAD                                                                 \
  KEYMAP(___, ___, ___, ___, ___, ___, ___, ___, ___, Key_Keypad7,             \
         Key_Keypad8, Key_Keypad9, Key_KeypadSubtract, ___, ___, ___, ___,     \
         ___, ___, ___, ___, ___, ___, Key_Keypad4, Key_Keypad5, Key_Keypad6,  \
         Key_KeypadAdd, ___, ___, ___, ___, ___, ___, ___, ___, Key_Keypad1,   \
         Key_Keypad2, Key_Keypad3, Key_Equals, Key_Quote, ___, ___, ___, ___,  \
         ___, ___, ___, ___, ___, Key_Keypad0, Key_KeypadDot,                  \
         Key_KeypadMultiply, Key_KeypadDivide, Key_Enter, Key_LeftControl,     \
         Key_Backspace, Key_LeftGui, Key_LeftShift, Key_RightShift,            \
         Key_RightAlt, Key_Spacebar, Key_RightControl, Key_Keymap1_Momentary,  \
         Key_Keymap1_Momentary)

#define QWERTY                                                                 \
  KEYMAP(Key_Delete, Key_1, Key_2, Key_3, Key_4, Key_5, LSHIFT(Key_9),         \
         LSHIFT(Key_0), Key_6, Key_7, Key_8, Key_9, Key_0, Key_PageUp,         \
         Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab, Key_Enter,  \
         Key_Y, Key_U, Key_I, Key_O, Key_P, Key_PageDown, Key_Minus, Key_A,    \
         Key_S, Key_D, Key_F, Key_G, Key_H, Key_J, Key_K, Key_L,               \
         Key_Semicolon, Key_Quote, Key_LeftBracket, Key_Z, Key_X, Key_C,       \
         Key_V, Key_B, Key_Equals, Key_Backslash, Key_N, Key_M, Key_Comma,     \
         Key_Period, Key_Slash, Key_RightBracket, M(MACRO_CC), Key_Backspace,  \
         M(MACRO_CX), M(MACRO_CH), M(MACRO_CG), M(MACRO_CX), Key_Spacebar,     \
         M(MACRO_CC), Key_KeymapNext_Momentary, Key_KeymapNext_Momentary)

KEYMAPS(QWERTY, GENERIC_FN2, NUMPAD)

enum {
  MAGIC_ESCAPE,
};

const macro_t *macroAction(uint8_t macroIndex, KeyEvent &event) {
  switch (macroIndex) {
  case MACRO_CC:
    event.key = OSM(LeftControl);
    return MACRO(D(LeftControl), T(C));
    break;

  case MACRO_CX:
    event.key = OSM(LeftControl);
    return MACRO(D(LeftControl), T(X));
    break;

  case MACRO_CH:
    event.key = OSM(LeftControl);
    return MACRO(D(LeftControl), T(H));
    break;

  case MACRO_CG:
    event.key = OSM(LeftControl);
    return MACRO(D(LeftControl), T(G));
    break;
  }

  return MACRO_NONE;
}

void magicEscape(uint8_t combo_index) {
  Macros.tap(Key_Escape);
}

USE_MAGIC_COMBOS([MAGIC_ESCAPE] = {.action = magicEscape, .keys = {R1C7, R1C8}});

KALEIDOSCOPE_INIT_PLUGINS(LEDControl, LEDOff,
                          ActiveModColorEffect,
                          NumPad,
                          Macros,
                          MouseKeys,
                          MagicCombo,
                          OneShot,
                          Qukeys);

void setup() {
QUKEYS(
    // left-side modifiers
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 1), Key_LeftGui),      // A
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 2), Key_LeftAlt),      // S
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 3), Key_LeftControl),  // D
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 4), Key_LeftShift),    // F
    // right-side modifiers
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 14), Key_LeftGui),     // :
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 13), Key_LeftAlt),     // L
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 12), Key_LeftControl), // K
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_LeftShift),   // J
  )


  // How much time must pass from the last key for the qukey's alternate effect
  // to be resolvable.
  Qukeys.setMinimumPriorInterval(75);
  // How much time must the qukey be held for its alternate state
  // to be resolvable.
  Qukeys.setMinimumHoldTime(120);
  // What fraction of the subsequent key can overlap with the qukey
  // for the qukey to activate alternate state.
  Qukeys.setOverlapThreshold(95);
  // How long we wait wait for a second tap to repeat the primary key.
  Qukeys.setMaxIntervalForTapRepeat(0);
  // How long does it take for the qukey to time out.
  Qukeys.setHoldTimeout(250);

  MouseKeys.speed = 4;
  MouseKeys.speedDelay = 0;
  MouseKeys.accelSpeed = 2;
  MouseKeys.accelDelay = 50;
  MouseKeys.setSpeedLimit(50);
  MouseKeys.wheelDelay = 60;

  OneShot.setTimeout(110);
  Kaleidoscope.setup();

  ActiveModColorEffect.highlight_color = CRGB(0xff, 0x00, 0x00);

  NumPad.numPadLayer = NUMPAD_KEYMAP;
  LEDOff.activate();
}


void loop() {
  Kaleidoscope.loop();
}
