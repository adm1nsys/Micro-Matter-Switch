// ===== Structures =====
struct DeviceDef {
  void (*logicFn)(void*);
  void (*setupFn)(void*);
  void (*loopFn)(void*);
};
// ===== include =====
#include <include.h>
// ===== BLE OR WiFi =====
#if BLE_MODE
  #define CONFIG_ENABLE_CHIPOBLE 1
  #define CHIP_DEVICE_CONFIG_ENABLE_THREAD 1
  #define CHIP_DEVICE_CONFIG_ENABLE_WIFI 0
#else
#if !CONFIG_ENABLE_CHIPOBLE
  #define CONFIG_ENABLE_CHIPOBLE 0
  #define CHIP_DEVICE_CONFIG_ENABLE_THREAD 0
  #define CHIP_DEVICE_CONFIG_ENABLE_WIFI 1
  #include <WiFi.h>
#endif
#endif
// ===== Logic =====
static inline void beforeSetup() {
  for (size_t i = 0; i < devicesCount; ++i) devices[i].logicFn(nullptr);
}
static inline void SetupScripts() {
  for (size_t i = 0; i < devicesCount; ++i) devices[i].setupFn(nullptr);
}
static inline void LoopScripts() {
  for (size_t i = 0; i < devicesCount; ++i) devices[i].loopFn(nullptr);
}
void startSNTP() {
  // KYIV: EET/EEST
  configTzTime("EET-2EEST,M3.5.0/3,M10.5.0/4", "pool.ntp.org", "time.google.com");
}
// ===== Arduino Core =====
bool blinkStep(uint8_t pin) {
  static uint8_t phase = 0;              // 0 — no blink, 1..6 — 3 cycles of 50ms (HIGH/LOW)
  static unsigned long t = 0;
  const unsigned long stepMs = 50;

  unsigned long now = millis();
  if (phase == 0) {                       // Start of blinks
    digitalWrite(pin, HIGH);
    t = now;
    phase = 1;
    return false;
  }
  if (now - t >= stepMs) {                // The next step every 50ms
    t += stepMs;
    digitalWrite(pin, (phase & 1) ? LOW : HIGH);
    if (++phase > 6) {                    // 3 cycles completed
      digitalWrite(pin, LOW);
      phase = 0;
      return true;                        // signal: pause for 200ms
    }
  }
  return false;
}
// ===== void setup =====
void setup(){
  // Serial.begin and pins
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // ===== Before Setup Logic =====
  beforeSetup();
  // CONFIG_ENABLE_CHIPOBLE is enabled when BLE is used to commission the Matter Network
#if !CONFIG_ENABLE_CHIPOBLE
  // Manually connect to WiFi
  // Before Matter.begin():
  WiFi.begin(ssid, password);
  // Wait for connection
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
#endif

  Matter.onEvent(onMatterEvent);
  Matter.begin();

  // ===== Void Setup Logic =====
  SetupScripts();
  if (!Matter.isDeviceCommissioned()) {
    Serial.println("\n=== Matter Over WiFi (BLE commissioning) ===");
    Serial.printf("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Serial.printf("QR code URL:        %s\n", Matter.getOnboardingQRCodeUrl().c_str());
    OnOffLight.updateAccessory(); /// NOTE: REMOVE
  } else {
    // Resumed
    Serial.printf("Resumed");
    // Add update logic to SetupScripts
  }

Serial.println(String("Matter.isDeviceCommissioned() Is connected? ") + Matter.isDeviceCommissioned());

}
// ===== void loop =====
void loop(){
  // ===== Paiting Mode =====
  static uint32_t lastNote = 0;
  if (!Matter.isDeviceCommissioned() && millis() - lastNote > 5000) {
    Serial.println("Waiting for commissioning…");
    lastNote = millis();
  }



// Pairing led blinking
if (!Matter.isDeviceCommissioned()) {
  if (blinkStep(ledPin)) {
    delay(200);
    UserEventsConnect();
  }
}

  // BOOT Button: Click calls UserEventsBootClick(); and HOLD for 5sec making Decommission
  if (digitalRead(buttonPin) == LOW && !btn_down) {
    btn_down = true;
    btn_ts = millis();
  }
  uint32_t dt = millis() - btn_ts;
  if (btn_down && dt > debounceMs && digitalRead(buttonPin) == HIGH) {
    btn_down = false;
    UserEventsBootClick();
  }
  if (btn_down && dt > decommissionHoldMs) {
    Serial.println("Decommissioning…");
    UserEventsDecommissioning();
    Matter.decommission();
    btn_ts = millis();
  }

  // ===== Void Loop Logic =====
  LoopScripts();
}