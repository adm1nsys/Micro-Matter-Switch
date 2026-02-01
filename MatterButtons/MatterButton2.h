#pragma once

// BTN3_SINK = 21 and BTN3_IN = 1

// ====== Hooks for DeviceImport (void(*)(void*)) ======
static void SmartButton2LogicBeforeSetup(void*) {
  // Setting up a "virtual ground" for button 3
  pinMode(BTN3_SINK, OUTPUT);
  digitalWrite(BTN3_SINK, LOW); 

  // Initialization of input and Matter EP
  pinMode(BTN3_IN, INPUT_PULLUP);
  SmartButton3.begin();
}

static void SmartButton2InSetup(void*) {
  // Logic after Matter.begin();
}

static void SmartButton2InLoop(void*) {
  
  // 1. Fixing the moment of pressing
  if (digitalRead(BTN3_IN) == LOW && !button3_state) {
    button3_time_stamp = millis();
    button3_state = true;
    Serial.println("Button 3 pressed...");
  }

  if (button3_state) {
    uint32_t time_diff = millis() - button3_time_stamp;

    // 2. Click Logic
    if (digitalRead(BTN3_IN) == HIGH) {
      if (time_diff > debouceTime && time_diff < decommissioningTimeout) {
        Serial.println("Button 3 released. Sending Click to Matter!");
        SmartButton3.click();
      }
      button3_state = false;
    }
    
    // 3. Decommissioning by holding the button
    else if (time_diff > decommissioningTimeout) {
      Serial.println("Decommissioning timeout reached via Button 3!");
      Matter.decommission();
      button3_state = false; 
    }
  }
}