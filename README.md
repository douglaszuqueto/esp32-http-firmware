# esp32-http-firmware

Firmware para ESP32 com suporte a integração com WebService e configuração via WiFiManager

## Bibliotecas

* [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
* [WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
* [Ticker](https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker)
* [HTTPClient](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)
* [Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences)
* [WiFiManager]()

## Arquitetura/Organização

Firmware dividido em arquivos. Cada arquivo com sua responsabilidade. Tudo isso visando melhor organização e facilidade em manter o código a longo prazo.

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/architecture.png)

## Diagrama de fluxo

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/diagrama-fluxo.png)

## Funcionalidades

* Configuração WiFi/Device via WifiManager
* Storage(Preferences)
* Ticker
* Cache(carregado no setup) - token, device_id, device_token, client_id
* Integração com webservice
* Autenticação e Autorização
* Renovação de token apenas quando expirado
* Suporte a debug
* Suporte a deepsleep

## Código principal

```arduino
void setup() {
  pinMode(LED, OUTPUT);
  ticker.attach(0.3, tick);

  initSerial();
  openStorage();

  setupWifiManager();

  makeCache();
  showConfig();
  
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
}
```

## Referências

* [Espressif - Arduino ESP32](https://github.com/espressif/arduino-esp32)
* [WiFi Manager](https://github.com/tzapu/WiFiManager)
* [WiFi Manager ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32)