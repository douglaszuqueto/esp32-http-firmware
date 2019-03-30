
String getFreeHeap() {
  return String(ESP.getFreeHeap());
}

String getHeapSize() {
  return String(ESP.getHeapSize());
}

// https://github.com/lucafabbri/HiGrow-Arduino-Esp/blob/master/HiGrowEsp32/HiGrowEsp32.ino
String getChipID() {
  char id[15];
  uint64_t chipid = ESP.getEfuseMac();
  sprintf(id, "ESP32-%08X", (uint32_t)chipid);

  return String(id);
}

void reboot() {
  DEBUG_PRINTLNC("[ESP] rebooting");
  esp_restart();
}

String getInfo() {
  String result;
  const size_t capacity = JSON_OBJECT_SIZE(20) + 2048;

  DynamicJsonDocument doc(capacity);
  JsonObject root = doc.to<JsonObject>();

  root["chipid"] = getChipID();
  root["fw_version"] = "1.2.0";
  root["ts"] = getTimestamp();
  root["ms"] = millis();
  root["boot_count"] = String(getBootCounter());
  root["heap_size"] = getHeapSize();
  root["free_heap"] = getFreeHeap();
  root["logs"] = preferences.getInt("logs");

  root["wifi_mode"] = int(WiFi.getMode());
  root["wifi_ssid"] = WiFi.SSID();
  root["wifi_ip"] = String(WiFi.localIP());
  root["wifi_mac"] = String(WiFi.macAddress());

  root["device_id"] = device_id;
  root["device_token"] = device_token;
  root["client_id"] = client_id;

  //  serializeJson(doc, result);
  serializeJsonPretty(doc, result);
  return result;
}

// https://github.com/esprfid/esp-rfid/blob/stable/src/helpers.esp#L1
String ICACHE_FLASH_ATTR printIP(IPAddress adress) {
  return (String)adress[0] + "." + (String)adress[1] + "." + (String)adress[2] + "." + (String)adress[3];
}

