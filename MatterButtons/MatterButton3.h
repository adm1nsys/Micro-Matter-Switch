#pragma once

// BTN4_SINK = 16 and BTN4_IN = 22

// ====== Hooks for DeviceImport (void(*)(void*)) ======
static void SmartButton3LogicBeforeSetup(void*) {
  // Setting up a "virtual ground" for button 4
  pinMode(BTN4_SINK, OUTPUT);
  digitalWrite(BTN4_SINK, LOW); 

  // Initialization of input and Matter EP
  pinMode(BTN4_IN, INPUT_PULLUP);
  SmartButton4.begin();
}

static void SmartButton3InSetup(void*) {
  // Logic after Matter.begin();
}

static void SmartButton3InLoop(void*) {
  
  // 1. Fixing the moment of pressing
  if (digitalRead(BTN4_IN) == LOW && !button4_state) {
    button4_time_stamp = millis();
    button4_state = true;
    Serial.println("Button 4 pressed...");
  }

  if (button4_state) {
    uint32_t time_diff = millis() - button4_time_stamp;

    // 2. Click Logic
    if (digitalRead(BTN4_IN) == HIGH) {
      if (time_diff > debouceTime && time_diff < decommissioningTimeout) {
        Serial.println("Button 4 released. Sending Click to Matter!");
        SmartButton4.click();
      }
      button4_state = false;
    }
    
    // 3. Decommissioning by holding the button
    else if (time_diff > decommissioningTimeout) {
      Serial.println("Decommissioning timeout reached via Button 4!");
      Matter.decommission();
      button4_state = false; 
    }
  }
}