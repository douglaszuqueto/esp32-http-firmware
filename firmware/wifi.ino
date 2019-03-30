
// https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiClientEvents/WiFiClientEvents.ino
void WiFiEvent(WiFiEvent_t event) {
  DEBUG_PRINTLNC("[WiFi events] event: %d\n" + event);

  switch (event) {
    case SYSTEM_EVENT_STA_CONNECTED:
      DEBUG_PRINTLNC(F("[WiFi] Connected to access point"));
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      DEBUG_PRINTLNC(F("[WiFi] Disconnected from WiFi access point"));
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      DEBUG_PRINTC(F("[WiFi] Obtained IP address: "));
      DEBUG_PRINTLN(WiFi.localIP());
      break;
  }
}

void setupWiFi() {
  WiFi.setAutoReconnect(true);
  WiFi.onEvent(WiFiEvent);

  DEBUG_PRINTC(F("[WIFI] IP: "));
  DEBUG_PRINTLN(WiFi.localIP());
}

void tick() {
  digitalWrite(LED, !digitalRead(LED));
}
