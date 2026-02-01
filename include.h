#pragma once

// ===== lib =====
#include <Matter.h>
#include <Arduino.h>
#include <Preferences.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/ConnectivityManager.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <lib/support/Span.h>   // chip::CharSpan
using namespace chip::DeviceLayer;
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_wifi.h"

#ifdef __cplusplus
}
#endif

#include <time.h>
#include <Mevent.h>
// ===== Matter EndPoint =====
/* NOTE:
 * 
 * If you want 2 the same EP in one time rename:
 * MatterColorLight ColorLight; // First
 * MatterColorLight ColorLight1; // Secound
 * Or use Lambda Single Callback Many Endpoints
 * 
 */
Preferences matterPref;

/* On/Off Light */
MatterOnOffLight OnOffLight;
/* Smart Button */
MatterGenericSwitch SmartButton;
MatterGenericSwitch SmartButton2;
MatterGenericSwitch SmartButton3;
MatterGenericSwitch SmartButton4;

// ===== Variables =====
#include <variables.h>
// ===== Logic =====
#include <MatterOnOffLight/MatterOnOffLight.h>
#include <MatterButtons/MatterButton.h>
#include <MatterButtons/MatterButton1.h>
#include <MatterButtons/MatterButton2.h>
#include <MatterButtons/MatterButton3.h>
// ===== Setup =====
#include <custom_connect.h>
#include <DeviceImport.h>

