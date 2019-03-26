void setupQueue() {
  DEBUG_PRINTLNC("[Queue] Setup");
  queue = xQueueCreate( queueSize, sizeof( Message ) );

  if (queue == NULL) {
    DEBUG_PRINTLNC("[Queue] Error creating the");
  }
}

void producerTask( void * parameter ) {
  Message message;

  while (true) {
    message.ID = random(10, 99);
    message.Data = "Ok, it's a message";

    unsigned int q_size = uxQueueMessagesWaiting(queue);

    DEBUG_PRINTLNC("[Producer] Sending to queue..." + String(q_size));
    xQueueSend(queue, &message, portMAX_DELAY);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void consumerTask( void * parameter) {
  Message message;

  while (true) {
    xQueueReceive(queue,  &message, portMAX_DELAY);
    DEBUG_PRINTC("[Consumer] ");
    DEBUG_PRINT(message.ID);
    DEBUG_PRINT(" | msg ");
    DEBUG_PRINT(message.Data);
    DEBUG_PRINT(" | ts ");
    DEBUG_PRINTLN(message.CreatedAt);

    writeEvent("INFO", "sensor", "read_data", message.Data, message.CreatedAt);
  }
}

