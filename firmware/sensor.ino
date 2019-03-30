
void setupSensor() {
  // ...
}

Message message;

void readSensor() {
  for (int i = 0; i < 8; i++) {
    y_axis[i] = random(10, 99);

    //writeLog("INFO", "sensor", "read_data", String(y_axis[i]), getTimestamp());

    sendDataSensorToQueue(i, String(y_axis[i]));
    delay(25);
  }
}

void sendDataSensorToQueue(int id, String data) {
  message.ID = id;
  message.Data = data;
  message.CreatedAt = getTimestamp();

  DEBUG_PRINTLNC("[Producer] Sending data sensor to queue");
  xQueueSend(queue, &message, portMAX_DELAY);
}

