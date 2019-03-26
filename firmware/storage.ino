
void openStorage() {
  DEBUG_PRINTLNC("[Storage] Setup");
  preferences.begin("esp-32", false);
}

void closeStorage() {
  preferences.end();
}

/************************* GET **********************/

void setDeviceToken(String str) {
  preferences.putString("device_token", str);
}

void setDeviceID(String str) {
  preferences.putString("device_id", str);
}

void setClientID(String str) {
  preferences.putString("client_id", str);
}

void setJWTToken(String str) {
  preferences.putString("jwt_token", str);

  strcpy(token, str.c_str());

  DEBUG_PRINTC(F("[HTTP] Token: "));
  DEBUG_PRINTLN(token);
}

/************************* SET **********************/

String getDeviceID() {
  String str = preferences.getString("device_id");

  return str;
}

String getDeviceToken() {
  String str = preferences.getString("device_token");

  return str;
}

String getClientID() {
  String str = preferences.getString("client_id");

  return str;
}

String getJWTToken() {
  String str = preferences.getString("jwt_token");

  return str;
}

void loadJWTToken() {
  strcpy(token, getJWTToken().c_str());
}

void makeCache() {
  strcpy(device_id, getDeviceID().c_str());
  strcpy(device_token, getDeviceToken().c_str());
  strcpy(client_id, getClientID().c_str());

  loadJWTToken();
}

void showConfig() {
  DEBUG_PRINTC(F("[CONFIG] API: "));
  DEBUG_PRINTLN(API_URL);

  DEBUG_PRINTC(F("[CONFIG] DeviceID: "));
  DEBUG_PRINTLN(device_id);

  DEBUG_PRINTC(F("[CONFIG] DeviceToken: "));
  DEBUG_PRINTLN(device_token);

  DEBUG_PRINTC(F("[CONFIG] ClientID: "));
  DEBUG_PRINTLN(client_id);
}

