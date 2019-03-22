
void handleError(int httpCode , String message ) {
  DEBUG_PRINTC(F("[HTTP] Code: "));
  DEBUG_PRINT(httpCode);
  DEBUG_PRINT(F(" | Message: "));
  DEBUG_PRINTLN(message);

  if (message == "token_expired") {
    DEBUG_PRINTLNC(F("[HTTP] requesting new token"));
    requestAccess();
  }
}

void requestAccess() {
  String p;

  p += "{";
  p += "\"id\":\"" + String(device_id) + "\"";
  p += ",\"password\":\"" + String(device_token) + "\"";
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
  p += "\"snr_1\":\"" + String(1) + "\"";
  p += ",\"snr_2\":\"" + String(2) + "\"";
  p += ",\"snr_3\":\"" + String(3) + "\"";
  p += ",\"snr_4\":\"" + String(4) + "\"";
  p += ",\"snr_5\":\"" + String(5) + "\"";
  p += ",\"snr_6\":\"" + String(6) + "\"";
  p += ",\"snr_7\":\"" + String(7) + "\"";
  p += ",\"snr_8\":\"" + String(8) + "\"";
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

  DEBUG_PRINTC(F("[HTTP] "));
  DEBUG_PRINTLN(response);

  return true;
}

