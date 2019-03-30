
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

void setupHTTP() {
  API_AUTH = API_URL + "/auth";
  API_SEND_DATA = API_URL + "/device/" + device_id;

  API_AUTH_PAYLOAD += "{";
  API_AUTH_PAYLOAD += "\"id\":\"" + String(device_id) + "\"";
  API_AUTH_PAYLOAD += ",\"password\":\"" + String(device_token) + "\"";
  API_AUTH_PAYLOAD += "}";
}

void requestAccess() {
  http.begin(API_AUTH);

  http.addHeader("content-type", "application/json");

  int httpCode = http.POST(API_AUTH_PAYLOAD);

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
  for (int i = 0; i < 8; i++) {
    if (i == 0)  {
      p += "\"snr_" + String(i + 1) + "\":\"" + String(y_axis[i]) + "\"";
      continue;
    }

    p += ",\"snr_" + String(i + 1) + "\":\"" + String(y_axis[i]) + "\"";
  }
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

