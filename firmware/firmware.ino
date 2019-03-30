/************************** Inclusão das Bibliotecas **************************/
#include <Arduino.h>
#include "user_config_override.h"

#include <WiFi.h>
#include <WebServer.h>
#include <Ticker.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include "time.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include <WiFiManager.h>

#if ESP_DASH && !DEEP_SLEEP
#include <ESPDash.h>
#endif

/************************* Variaveis globais **********************/

#define LED 2

String API_AUTH = "";
String API_SEND_DATA = "";
String API_AUTH_PAYLOAD = "";

char device_id[40];
char device_token[70];
char client_id[40];

char token[500];

bool shouldSaveConfig = false;

uint32_t sleep_time = 60 * 1000000; // intervalo de 1 minuto

const char* ntpServer = "a.st1.ntp.br";
const long  gmtOffset_sec = -3 * 3600;
const int   daylightOffset_sec = 0;

int x_axis_size = 8;
String x_axis[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
int y_axis_size = 8;
int y_axis[8] = {0, 0, 0, 0, 0, 0, 0, 0};

typedef struct {
  int ID;
  String Data;
  String CreatedAt;
} Message;

int queueSize = 10;
int maxLogSize = 20;
bool isStartedWebServer = false;

/**************************** DEBUG *******************************/

#if DEBUG
#define DEBUG_PRINTLN(m) Serial.println(m)
#define DEBUG_PRINT(m) Serial.print(m)

#define DEBUG_PRINTLNC(m) Serial.println("Core " + String(xPortGetCoreID()) + " - " + m)
#define DEBUG_PRINTC(m) Serial.print("Core " + String(xPortGetCoreID()) + " - " + m)

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
QueueHandle_t queue;
AsyncWebServer server(8080);

#if ESP_DASH && !DEEP_SLEEP
AsyncWebServer server(80);
#endif

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
  setupStorage();
  setupWifiManager();
  setupWiFi();
  setupNtp();
  setupQueue();

  makeCache();
  setupHTTP();

  showConfig();

#if DEEP_SLEEP
  sendData();
  closeStorage();
  DEBUG_PRINTLNC(F("[ESP] Sleeping..."));
  ESP.deepSleep(sleep_time);
#endif

#if ESP_DASH && !DEEP_SLEEP
  initEspDash();
#endif

  delay(1000);
  initTasks();
  incrementBootCounter();
  ticker.detach();
  digitalWrite(LED, LOW);
}

void loop() {
}

