# esp32-http-firmware

Firmware para ESP32 com suporte a integração com WebService e configuração via WiFiManager

## Posts relacionados

Se você chegou até aqui e esta boiando sobre o que originou este projeto, recomendo ver os posts que fiz no [Grupo Arduino Brasil](https://www.facebook.com/groups/arduino.br) no Facebook!

* [1º post](https://www.facebook.com/groups/arduino.br/permalink/2228450170527406/)
* [2º post](https://www.facebook.com/groups/arduino.br/permalink/2231466933559063/)

## Bibliotecas

* [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
* [WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
* [Ticker](https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker)
* [HTTPClient](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)
* [Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences)
* [WiFiManager]()

## Arquitetura/Organização

Firmware dividido em arquivos. Cada arquivo com sua responsabilidade. Tudo isso visando melhor organização e facilidade em manter o código a longo prazo.

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/architecture-2.png)

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

```c
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
```

## WifiManager

Página de configuração via wifi manager

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/wifimanager.png)

## Monitor serial
Um pouco do fluxo que ocorre após o salvamento das configurações no wifi manager

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/serial-monitor.png)

## Referências

* [Espressif - Arduino ESP32](https://github.com/espressif/arduino-esp32)
* [WiFi Manager](https://github.com/tzapu/WiFiManager)
* [WiFi Manager ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32)