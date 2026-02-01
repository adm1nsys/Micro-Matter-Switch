#pragma once

const char *nsName = "MatterPrefs";
const char *onOffKey = "OnOff";

constexpr int relayPin = 21;
uint8_t useBuItINLed = 1;

bool setLightOnOff(bool state) {
  digitalWrite(relayPin, state ? LOW : HIGH);
  if (useBuItINLed) {
  digitalWrite(ledPin, state ? LOW : HIGH);
  }
  matterPref.putBool(onOffKey, state);
  return true;
}

// Identification shall be done by Blink in Red or just the GPIO when no LED_BUILTIN is not defined
bool onIdentifyLightCallback(bool identifyIsActive) {
  Serial.printf("Identify Cluster is %s\r\n", identifyIsActive ? "Active" : "Inactive");
  if (identifyIsActive) {
    // Start Blinking the light in loop()
    identifyFlag = false;
    Serial.printf("toggle ");
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
    delay(300);
    OnOffLight.toggle();
  } else {
    // Stop Blinking and restore the light to the its last state
    identifyFlag = false;
    // force returning to the original state by toggling the light twice
    Serial.printf("toggle no");

  }
  return true;
}

void OnOffLogicBeforeSetup(void*) { 
  pinMode(relayPin, OUTPUT);
  if (Matter.isDeviceCommissioned()) {
    OnOffLight.updateAccessory();
  } 
  matterPref.begin(nsName, false);
  bool last = matterPref.getBool(onOffKey, true);
  OnOffLight.begin(last);
  OnOffLight.onChange(setLightOnOff);
  OnOffLight.onIdentify(onIdentifyLightCallback);
 }

void OnOffinSetup(void*) { 
  if (Matter.isDeviceCommissioned()) {
    Serial.printf("Resumed. Initial state: %s\n", OnOffLight.getOnOff() ? "ON" : "OFF");
    OnOffLight.updateAccessory();
  }
}

void OnOffinLoop(void*) {

  if (digitalRead(buttonPin) == LOW && !btn_down) {
    btn_down = true;
    btn_ts = millis();
  }

  if (digitalRead(buttonPin) == LOW && !btn_down) {
      delay(50);
    if (digitalRead(buttonPin) == HIGH) {
      OnOffLight.setOnOff(!OnOffLight.getOnOff());
      OnOffLight.updateAccessory();
    }
  }

  uint32_t dt = millis() - btn_ts;
  if (btn_down && dt > debounceMs && digitalRead(buttonPin) == HIGH) {
    btn_down = false;
      OnOffLight.setOnOff(!OnOffLight.getOnOff());
      OnOffLight.updateAccessory();
  }
}

