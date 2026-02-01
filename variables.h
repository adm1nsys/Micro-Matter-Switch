#pragma once

// ===== BLE MODE =====
#define BLE_MODE 1 // true 1 / false 0
// ===== if BLE MODE 0 =====
#if !BLE_MODE
  const char *ssid = "SSID";          // Change this to your WiFi SSID
  const char *password = "PASSWORD";  // Change this to your WiFi password
#endif

const uint32_t decommissionHoldMs = 5000;
const uint32_t debounceMs = 250;
bool btn_down = false;
uint32_t btn_ts = 0;
bool blinkStep(uint8_t pin);
volatile bool identifyFlag = false;     // Flag to start the Blink when in Identify state

// -------- Buttons pins --------
constexpr uint8_t BTN1_IN   = 18; // D10 (to GND), active LOW
constexpr uint8_t BTN2_IN   = 17; // D7  -> input with PULLUP
constexpr uint8_t BTN2_SINK = 20; // D9  -> output LOW
constexpr uint8_t BTN3_IN   = 1;  // G1  -> input with PULLUP
constexpr uint8_t BTN3_SINK = 21; // D3  -> output LOW
constexpr uint8_t BTN4_IN   = 22; // D4  -> input with PULLUP
constexpr uint8_t BTN4_SINK = 16; // D6  -> output LOW

// ===== LED on Board and BOOT Button =====
#ifdef LED_BUILTIN
  const uint8_t ledPin = LED_BUILTIN;
#else
  const uint8_t ledPin = 2;  // Set your pin here if your board has not defined LED_BUILTIN
#endif
const uint8_t buttonPin = BOOT_PIN;

uint32_t button1_time_stamp = 0;                // debouncing control
bool button1_state = false;                     // false = released | true = pressed

uint32_t button2_time_stamp = 0;                // debouncing control
bool button2_state = false;                     // false = released | true = pressed

uint32_t button3_time_stamp = 0;                // debouncing control
bool button3_state = false;                     // false = released | true = pressed

uint32_t button4_time_stamp = 0;                // debouncing control
bool button4_state = false;                     // false = released | true = pressed

const uint32_t debouceTime = 250;              // button debouncing time (ms)
const uint32_t decommissioningTimeout = 5000;  // keep the button pressed for 5s, or longer, to decommission