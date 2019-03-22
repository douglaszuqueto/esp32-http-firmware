# ESP32 HTTP Firmware - V2

Firmware para ESP32 com suporte a integração com WebService e configuração via WiFiManager

## Versões

* [V1](https://github.com/douglaszuqueto/esp32-http-firmware/tree/1.0.0)

## Posts relacionados

Se você chegou até aqui e esta boiando sobre o que originou este projeto, recomendo ver os posts que fiz no [Grupo Arduino Brasil](https://www.facebook.com/groups/arduino.br) no Facebook!

* [1º post](https://www.facebook.com/groups/arduino.br/permalink/2228450170527406/)
* [2º post](https://www.facebook.com/groups/arduino.br/permalink/2231466933559063/)
* [3º post](https://www.facebook.com/groups/arduino.br/permalink/2234227333283023/)

## Bibliotecas

* [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
* [WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
* [Ticker](https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker)
* [HTTPClient](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)
* [Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences)
* [WiFiManager](https://github.com/tzapu/WiFiManager)
* [ESP-DASH](https://github.com/ayushsharma82/ESP-DASH)
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)


## Arquitetura/Organização

Firmware dividido em arquivos. Cada arquivo com sua responsabilidade. Tudo isso visando melhor organização e facilidade em manter o código a longo prazo.

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/architecture-v2.png)

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
* Visualização através do webapp embarcado
* Multi-tarefas

## Código principal

```c
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
```

## Tasks
X tarefas são criadas. Elas serão distribuidas e gerenciadas através do RTOS de forma automática.

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/tasks.png)

## WifiManager

Página de configuração via wifi manager

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/wifimanager.png)

## ESP-DASH
Como brincadeira adicional acabei conhecendo o projeto [ESP-DASH](https://github.com/ayushsharma82/ESP-DASH) em um grupo, dei uma olhada e gostei bastante das funcionalidades e da arquitetura que foi aplicada no projeto.

Ainda não tem nenhuma integração, mas o mesmo possui uma tarefa na qual atualizada os dados de X em X tempo. Também possui um botão no qual possui interação com o led.

É um projeto muito bacana, pois foi embarcado um WebAPP desenvolvido em VueJS e o build('compilação') desse webapp é embarcado dentro do esp através do SPIFFS - uma técnica deveras interessante que pode agregar muito nos projetos!

Outro fato legal que eu gostei bastante, é que toda comunicação ocorre em 'tempo real' através do uso de websockets. Então além do ESP32 atuar como webserver servindo o webapp também cria um servidor de websockets, interessante não é?!

* Dashboard

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/esp-dash.png)

* Stats

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/esp-dash-stats.png)

## Monitor serial
Um pouco do fluxo que ocorre após o salvamento das configurações no wifi manager.

No monitor serial houve uma melhoria que agora possibilita ver em qual core as tasks estão rodando em tempo de execução.

![img](https://raw.githubusercontent.com/douglaszuqueto/esp32-http-firmware/master/.github/serial-monitor-v2.png)

## Referências

* [Espressif - Arduino ESP32](https://github.com/espressif/arduino-esp32)
* [WiFi Manager](https://github.com/tzapu/WiFiManager)
* [WiFi Manager ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32)