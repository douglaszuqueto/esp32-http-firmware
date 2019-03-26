
void ICACHE_FLASH_ATTR writeEvent(String type, String src, String desc, String data, String timestamp) {
  StaticJsonDocument<200> root;
  root["type"] = type;
  root["src"] = src;
  root["desc"] = desc;
  root["data"] = data;
  root["created_at"] = timestamp;
  String result;
  serializeJson(root, result);

  File eventlog = SPIFFS.open("/eventlog.json", "a");
  eventlog.print(result);

  eventlog.print("\n");
  eventlog.close();

  int logs = preferences.getInt("logs");
  preferences.putInt("logs", (logs + 1));

  DEBUG_PRINTLNC("[Log] Saved: " + desc);
}

void checkLogSize() {
  int logs = preferences.getInt("logs");

  if (logs > 100) {
    if (SPIFFS.remove("/eventlog.json")) {
      DEBUG_PRINTLNC("[Log] File deleted");
    } else {
      DEBUG_PRINTLNC("[Log] Delete failed");
    }
    preferences.putInt("logs", 0);
  }
}

String ICACHE_FLASH_ATTR sendEventLog(int page) {
  DynamicJsonDocument doc(50000);
  JsonArray array = doc.to<JsonArray>();

  File eventlog = SPIFFS.open("/eventlog.json", "r");

  while (eventlog.available()) {
    String item = eventlog.readStringUntil('\n');

    array.add(item);
  }
  eventlog.close();

  String result;
  serializeJson(doc, result);

  return result;
}
