#pragma once

// Prototype so that Mevent.h can see the function
void startSNTP();   // external function
static void onMatterEvent(matterEvent_t type,
                          const chip::DeviceLayer::ChipDeviceEvent* info) {
  switch (type) {
    case MATTER_SERVER_READY: {
      // Wi-Fi is already inicialized - can use esp_wifi_*
      wifi_country_t c = {};
      strncpy(c.cc, "UA", sizeof(c.cc)); // Better to set your country code
      c.schan  = 1;
      c.nchan  = 13;
      c.policy = WIFI_COUNTRY_POLICY_MANUAL;

      esp_wifi_set_ps(WIFI_PS_NONE);
      esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
      esp_wifi_set_country(&c);

      // >>> Installing NodeLabel
auto status = chip::app::Clusters::BasicInformation::Attributes::NodeLabel::Set(
    /*endpointId=*/0, chip::CharSpan::fromCharString("MMS by adm1nsys"));
if (status != chip::Protocols::InteractionModel::Status::Success) {
  Serial.printf("Failed to set NodeLabel, status: %u\n", (unsigned)status);
} else {
  Serial.println("NodeLabel set OK");
}
      // <<<

      break;
    }

    case MATTER_INTERFACE_IP_ADDRESS_CHANGED: {
      esp_wifi_set_ps(WIFI_PS_NONE);
      startSNTP();
      break;
    }

    case MATTER_WIFI_CONNECTIVITY_CHANGE: {
      esp_wifi_set_ps(WIFI_PS_NONE);
      break;
    }

    default:
      break;
  }
}

