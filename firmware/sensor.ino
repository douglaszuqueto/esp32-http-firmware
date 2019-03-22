
void setupSensor() {
  // ...
}

void readSensor() {
  for (int i = 0; i < 7; i++) {
    y_axis[i] = random(0, 30);
  }
}
