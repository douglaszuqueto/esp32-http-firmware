
void setupWebServer() {
  DEBUG_PRINTLNC("[WS] Setup");

  startHandlers();
  server.begin();

  DEBUG_PRINTLNC("[WS] begin");
}

void startHandlers() {
  server.on("/log", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", getLogs());
  });

  server.on("/info", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", getInfo());
  });

  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ok");
    reboot();
  });

  server.on("/boot_reset", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ok");
    resetBootCounter();
  });

  server.onNotFound([](AsyncWebServerRequest * request) {
    DEBUG_PRINTLNC("[WS] NOT_FOUND: ");
    request->send(404);
  });
}

