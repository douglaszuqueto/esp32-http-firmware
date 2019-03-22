
void WiFiEvent(WiFiEvent_t event) {
  DEBUG_PRINTLNC("[WiFi-event] event: %d\n" + event);

  switch (event) {
    case SYSTEM_EVENT_STA_DISCONNECTED:
      DEBUG_PRINTLNC(F("[WiFi] Disconnected from WiFi access point"));
      break;
  }
}

void setupWiFi() {
  WiFi.setAutoReconnect(true);
  WiFi.onEvent(WiFiEvent);

  DEBUG_PRINTC(F("[WIFI] IP: "));
  DEBUG_PRINTLNC(WiFi.localIP());
}

void tick() {
  int state = digitalRead(LED);
  digitalWrite(LED, !state);
}
