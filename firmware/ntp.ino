
void setupNtp() {
  DEBUG_PRINTLN("[NTP] Setup");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  DEBUG_PRINTLNC("[NTP] Setup");
  DEBUG_PRINTC("[NTP] Now: ");
  DEBUG_PRINTLN(getTimestamp());
}

String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    DEBUG_PRINTLNC("Failed to obtain time");
    return "";
  }

  time_t now;
  time(&now);

  return String(now);
}
