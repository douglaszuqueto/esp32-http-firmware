/************************** Inclusão das Bibliotecas **************************/

#include <WiFi.h>
#include <WebServer.h>
#include <Ticker.h>
#include <HTTPClient.h>
#include <Preferences.h>

#include <WiFiManager.h>

/************************* Variaveis globais **********************/

#define DEBUG true
#define DEEP_SLEEP false

#define LED 2

String API_URL = "http://127.0.0.1:5000/api";
String API_AUTH = "";
String API_SEND_DATA = "";

char device_id[40];
char device_token[70];
char client_id[40];

char token[500];

bool shouldSaveConfig = false;

uint32_t sleep_time = 60 * 1000000; // intervalo de 1 minuto


/**************************** DEBUG *******************************/

#if DEBUG
#define DEBUG_PRINTLN(m) Serial.println(m)
#define DEBUG_PRINT(m) Serial.print(m)

#else
#define DEBUG_PRINTLN(m)
#define DEBUG_PRINT(m)

#endif

/************************* Instanciação dos objetos  **************************/

Ticker ticker;
WiFiClient client;
HTTPClient http;
Preferences preferences;

/************************* Declaração dos Prototypes **************************/

void initSerial();
void openStorage();
void setupWifiManager();
void requestAccess();
bool sendData();
void handleError(int httpCode , String message);

/********************************** Sketch ************************************/

void setup() {
  pinMode(LED, OUTPUT);
  ticker.attach(0.3, tick);

  initSerial();
  openStorage();

  setupWifiManager();

  makeCache();
  showConfig();

  //
  API_AUTH = API_URL + "/auth";
  API_SEND_DATA = API_URL + "/device/" + device_id;
  //

  requestAccess();

  ticker.detach();
  digitalWrite(LED, LOW);

#if DEEP_SLEEP
  sendData();
  closeStorage();
  DEBUG_PRINTLN("[ESP] Sleeping...");
  ESP.deepSleep(sleep_time);
#endif
}

void loop() {
  delay(2000);
  sendData();
  yield();
}

