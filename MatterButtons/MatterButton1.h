#pragma once

// BTN2_SINK = 20 and BTN2_IN = 17

// ====== Hooks for DeviceImport (void(*)(void*)) ======
static void SmartButton1LogicBeforeSetup(void*) {
  // Setting up a "virtual ground" for button 2
  pinMode(BTN2_SINK, OUTPUT);
  digitalWrite(BTN2_SINK, LOW); 

  // Initialization of input and Matter EP
  pinMode(BTN2_IN, INPUT_PULLUP);
  SmartButton2.begin();
}

static void SmartButton1InSetup(void*) {
  // Logic after Matter.begin();
}

static void SmartButton1InLoop(void*) {
  
  // 1. Fixing the moment of pressing
  if (digitalRead(BTN2_IN) == LOW && !button2_state) {
    button2_time_stamp = millis();
    button2_state = true;
    Serial.println("Button 2 pressed...");
  }

  if (button2_state) {
    uint32_t time_diff = millis() - button2_time_stamp;

    // 2. Click Logic
    if (digitalRead(BTN2_IN) == HIGH) {
      if (time_diff > debouceTime && time_diff < decommissioningTimeout) {
        Serial.println("Button 2 released. Sending Click to Matter!");
        SmartButton2.click();
      }
      button2_state = false;
    }
    
    // 3. Decommissioning by holding the button
    else if (time_diff > decommissioningTimeout) {
      Serial.println("Decommissioning timeout reached via Button 2!");
      Matter.decommission();
      button2_state = false; 
    }
  }
}