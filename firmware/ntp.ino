
void setupNtp() {
  DEBUG_PRINTLNC("[NTP] Setup");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  DEBUG_PRINTC("[NTP] Now: ");
  DEBUG_PRINTLN(getTimestamp());
}

String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    DEBUG_PRINTLNC("[NTP] Failed to obtain time");
    return "";
  }

  time_t now;
  time(&now);

  return String(now);
}
