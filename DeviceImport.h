#pragma once

// Array of POINTERS to functions (NOT strings)
static DeviceDef devices[] = {
  // OnOff
  { &OnOffLogicBeforeSetup, &OnOffinSetup, &OnOffinLoop },
  // Smart Button
  { &SmartButtonLogicBeforeSetup, &SmartButtonInSetup, &SmartButtonInLoop },
  { &SmartButton1LogicBeforeSetup, &SmartButton1InSetup, &SmartButton1InLoop },
  { &SmartButton2LogicBeforeSetup, &SmartButton2InSetup, &SmartButton2InLoop },
  { &SmartButton3LogicBeforeSetup, &SmartButton3InSetup, &SmartButton3InLoop },
};

static const size_t devicesCount = sizeof(devices)/sizeof(devices[0]);