void tick()
{
  int state = digitalRead(LED);
  digitalWrite(LED, !state);
}
