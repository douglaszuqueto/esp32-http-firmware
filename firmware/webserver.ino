
void setupWebServer() {
  DEBUG_PRINTLNC("[WS] Setup");
  
  server.on("/log", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", sendEventLog(0));
  });

  server.onNotFound([](AsyncWebServerRequest * request) {
    DEBUG_PRINTLNC("[WS] NOT_FOUND: ");
    request->send(404);
  });

  server.begin();
  DEBUG_PRINTLNC("[WS] begin");
}
