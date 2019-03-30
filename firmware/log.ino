
void resetLogCounter() {
  DEBUG_PRINTLNC("[Log] set counter to 0");
  preferences.putInt("logs", 0);
}

void incrementLogCounter() {
  int logs = preferences.getInt("logs");
  preferences.putInt("logs", (logs + 1));
}

void checkLogSize() {
  int logs = preferences.getInt("logs");

  if (logs >= maxLogSize) {
    resetLogCounter();
  }
}

void writeLog(String type, String src, String desc, String data, String timestamp) {
  String result;
  StaticJsonDocument<500> root;

  root["type"] = type;
  root["src"] = src;
  root["desc"] = desc;
  root["data"] = data;
  root["created_at"] = timestamp;
  serializeJson(root, result);

  checkLogSize();

  int logs = preferences.getInt("logs");
  String idx = "log_" + String(logs);
  preferences.putString(idx.c_str(), result);

  incrementLogCounter();
  DEBUG_PRINTLNC("[Log] Saved: " + desc);
}

String ICACHE_FLASH_ATTR getLogs() {
  String result;
  const size_t capacity = JSON_ARRAY_SIZE((maxLogSize + 10)) + 2048;

  DynamicJsonDocument doc(capacity);
  JsonArray array = doc.to<JsonArray>();

  for (int i = 0; i < 20; i++ ) {
    String idx = "log_" + String(i);
    String item = preferences.getString(idx.c_str());

    array.add(item);
  }

  serializeJsonPretty(doc, result);

  return result;
}
