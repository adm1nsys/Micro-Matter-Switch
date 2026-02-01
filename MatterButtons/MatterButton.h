#pragma once

// BTN1_IN = 18 to GND

// ====== Hooks for DeviceImport (void(*)(void*)) ======
static void SmartButtonLogicBeforeSetup(void*) {
  // Initialization of pins and Matter EP
  pinMode(BTN1_IN, INPUT_PULLUP);
  SmartButton.begin();
}

static void SmartButtonInSetup(void*) {
  // Logic after Matter.begin();
}

static void SmartButtonInLoop(void*) {

  // 1. Fixing the moment of pressing
  if (digitalRead(BTN1_IN) == LOW && !button1_state) {
    button1_time_stamp = millis();
    button1_state = true;
    Serial.println("Button 1 pressed...");
  }

  if (button1_state) {
    uint32_t time_diff = millis() - button1_time_stamp;

    // 2. Click Logic
    if (digitalRead(BTN1_IN) == HIGH) {
      if (time_diff > debouceTime && time_diff < decommissioningTimeout) {
        Serial.println("User button released. Sending Click to Matter!");
        SmartButton.click();
      }
      button1_state = false;
    }
    
    // 3. Decommissioning by holding the button
    else if (time_diff > decommissioningTimeout) {
      Serial.println("Decommissioning timeout reached. Resetting Matter node...");
      Matter.decommission();
      
      // Reset the variable state to avoid the decommissioning process from looping until reboot.
      button1_state = false; 
    }
  }
}