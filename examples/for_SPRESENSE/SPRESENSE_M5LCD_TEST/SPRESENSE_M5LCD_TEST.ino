void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("SPRESENSE-M5LCD Test");
  Serial2.println("M5.Lcd.println(\"SPRESENSE-M5LCD Test\")");
}

int FSM = 0;

void loop() {
  delay(1000);
  Serial.println(FSM);
  Serial2.println("M5.Lcd.fillScreen(RED)");
  Serial2.println("M5.Lcd.setTextSize(2)");
  Serial2.println("M5.Lcd.setCursor(10," + String(FSM * 20) + "\")");
  Serial2.println("M5.Lcd.setTextColor(BLACK, GREEN)");
  Serial2.println("M5.Lcd.print(\"SPRESENSE\")");
  Serial2.println("M5.Lcd.println(\" M5LCD Test\")");
  FSM++;
  if(FSM > 11){
    FSM = 0;
  }
}
