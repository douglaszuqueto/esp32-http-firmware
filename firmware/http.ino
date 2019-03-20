
void handleError(int httpCode , String message ) {
  DEBUG_PRINT("[HTTP] Code: " + String(httpCode));
  DEBUG_PRINTLN(" | Message: " + message);

  if (message == "token_expired") {
    DEBUG_PRINTLN("[HTTP] requesting new token");
    requestAccess();
  }
}

void requestAccess() {
  String p;

  p += "{";
  p += "\"id\":";
  p += "\"37e73144-af71-4fde-93ab-98d1d6a6f83f\"";
  p += ",\"password\":";
  p += "\"f7a7329f391bc2a6d3141fb2b867cbdb637fed874aea8ae9c658418817a67ea4\"";
  p += "}";

  http.begin(API_AUTH);

  http.addHeader("content-type", "application/json");

  int httpCode = http.POST(p);

  String response =  http.getString();
  http.end();

  if (httpCode != HTTP_CODE_OK) {
    handleError(httpCode, response);
    return;
  }

  setJWTToken(response);
}

bool sendData() {
  ticker.attach(0.1, tick);
  
  String p;
  p += "{";
  p += "\"snr_1\":";
  p += "\"0\"";
  p += ",\"snr_2\":";
  p += "\"0\"";
  p += ",\"snr_3\":";
  p += "\"0\"";
  p += ",\"snr_4\":";
  p += "\"0\"";
  p += ",\"snr_5\":";
  p += "\"0\"";
  p += ",\"snr_6\":";
  p += "\"0\"";
  p += ",\"snr_7\":";
  p += "\"0\"";
  p += ",\"snr_8\":";
  p += "\"0\"";
  p += "}";

  http.begin(API_SEND_DATA);

  http.addHeader("Authorization", token);
  http.addHeader("ClientID", client_id);

  int httpCode = http.POST(p);

  String response =  http.getString();
  http.end();

  ticker.detach();
  digitalWrite(LED, LOW);

  if (httpCode != HTTP_CODE_OK) {
    handleError(httpCode, response);
    return false;
  }

  DEBUG_PRINTLN("[HTTP] " + response);
  return true;
}

