/************************** Inclusão das Bibliotecas **************************/
#include <Arduino.h>
#include "user_config_override.h"

#include <WiFi.h>
#include <WebServer.h>
#include <Ticker.h>
#include <HTTPClient.h>
#include <Preferences.h>

#include <WiFiManager.h>

#if ESP_DASH
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>
#endif

/************************* Variaveis globais **********************/

#define LED 2

String API_AUTH = "";
String API_SEND_DATA = "";

char device_id[40];
char device_token[70];
char client_id[40];

char token[500];

bool shouldSaveConfig = false;

uint32_t sleep_time = 60 * 1000000; // intervalo de 1 minuto

int x_axis_size = 7;
String x_axis[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int y_axis_size = 7;
int y_axis[7] = {2, 5, 10, 12, 18, 8, 5};

/**************************** DEBUG *******************************/

#if DEBUG
#define DEBUG_PRINTLN(m) Serial.println(m)
#define DEBUG_PRINT(m) Serial.print(m)

#define DEBUG_PRINTLNC(m) Serial.println("[Core " + String(xPortGetCoreID()) + "]" + m)
#define DEBUG_PRINTC(m) Serial.print("[Core " + String(xPortGetCoreID()) + "]" + m)

#else
#define DEBUG_PRINTLN(m)
#define DEBUG_PRINT(m)
#define DEBUG_PRINTLNC(m)
#define DEBUG_PRINTC(m)
#endif

/************************* Instanciação dos objetos  **************************/

Ticker ticker;
WiFiClient client;
HTTPClient http;
Preferences preferences;

#if ESP_DASH
AsyncWebServer server(80);
#endif

/************************* Declaração dos Prototypes **************************/

void initSerial();
void openStorage();
void setupWifiManager();
void requestAccess();
bool sendData();
void handleError(int httpCode , String message);

void buttonClicked(const char* id) {
  DEBUG_PRINTLNC("Button Clicked - " + String(id));
  digitalWrite(LED, !digitalRead(LED));
}

/********************************** Sketch ************************************/

void setup() {
  pinMode(LED, OUTPUT);
  ticker.attach(0.3, tick);

  initSerial();
  openStorage();

  setupWifiManager();
  setupWiFi();

  makeCache();
  showConfig();

  //
  API_AUTH = API_URL + "/auth";
  API_SEND_DATA = API_URL + "/device/" + device_id;
  //

  requestAccess();

  ticker.detach();
  digitalWrite(LED, LOW);

#if ESP_DASH
  initEspDash();
#endif

#if DEEP_SLEEP
  sendData();
  closeStorage();
  DEBUG_PRINTLNC(F("[ESP] Sleeping..."));
  ESP.deepSleep(sleep_time);
#endif

  delay(1000);
  initTasks();
}

void loop() {
}

