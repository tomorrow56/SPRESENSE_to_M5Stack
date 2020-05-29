#include <M5Stack.h>
#include "M5StackUpdater.h"

#define debug false

void setup() {
  M5.begin();

  if(digitalRead(BUTTON_A_PIN) == 0){                // SD Update
     updateFromFS(SD);
     ESP.restart();
  }

//  Serial.begin(115200);
  Serial.println("Hello!");
  M5.Lcd.println("Hello!");
  
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  
  // Reset Spresense
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  delay(1000);  
  digitalWrite(15, HIGH);
}

String readChar = "";
 
void loop() {
  M5.update();
  if(M5.BtnC.wasPressed()){
    Serial.println("Reset SPRESENSE...");
    digitalWrite(15, LOW);
  }

  if(M5.BtnC.wasReleased()){
    digitalWrite(15, HIGH);
  }

  if(Serial2.available()) {
    int ch = Serial2.read();
    if(debug == true){
      Serial.write(ch);
    }
    if(ch == 0x0a){
    }else{
      readChar = readChar + (char)ch;
    }
    if(ch == 0x0d){
      if(readChar.startsWith("M5.Lcd.")){
        LcdString(readChar.substring(7));
      }
      readChar = "";
    }
  }
}

String extractString(String drawCommand){
  String outChar = drawCommand;
  outChar.replace("(","");
  outChar.replace(")","");
  outChar.trim();
  outChar.replace("\"","");
  return outChar;
}

String splitString(String drawCommand, String Delimiter){
  String outChar = drawCommand;
  outChar.replace("(","");
  outChar.replace(")","");
  outChar.trim();
  outChar.replace("\"","");
  return outChar;
}


uint16_t String2Color(String outChar){
  uint16_t lcdColor;
  if(outChar.startsWith("BLACK")){
    lcdColor = BLACK;
  }else if(outChar.startsWith("NAVY")){
    lcdColor = NAVY;
  }else if(outChar.startsWith("DARKGREEN")){
    lcdColor = DARKGREEN;
  }else if(outChar.startsWith("DARKCYAN")){
    lcdColor = DARKCYAN;
  }else if(outChar.startsWith("MAROON")){
    lcdColor = MAROON;
  }else if(outChar.startsWith("PURPLE")){
    lcdColor = PURPLE;
  }else if(outChar.startsWith("OLIVE")){
    lcdColor = OLIVE;
  }else if(outChar.startsWith("LIGHTGREY")){
    lcdColor = LIGHTGREY;
  }else if(outChar.startsWith("DARKGREY")){
    lcdColor = DARKGREY;
  }else if(outChar.startsWith("BLUE")){
    lcdColor = BLUE;
  }else if(outChar.startsWith("GREEN")){
    lcdColor = GREEN;
  }else if(outChar.startsWith("CYAN")){
    lcdColor = CYAN;
  }else if(outChar.startsWith("RED")){
    lcdColor = RED;
  }else if(outChar.startsWith("MAGENTA")){
    lcdColor = MAGENTA;
  }else if(outChar.startsWith("YELLOW")){
    lcdColor = YELLOW;
  }else if(outChar.startsWith("WHITE")){
    lcdColor = WHITE;
  }else if(outChar.startsWith("ORANGE")){
    lcdColor = ORANGE;
  }else if(outChar.startsWith("GREENYELLOW")){
    lcdColor = GREENYELLOW;
  }else if(outChar.startsWith("PINK")){
    lcdColor = PINK;
  }else{
    lcdColor = BLACK;
  }

  return lcdColor;
}
void LcdString(String drawCommand){
  String outChar = "";
  if(drawCommand.startsWith("println(")){
    outChar = drawCommand.substring(7);
    M5.Lcd.println(extractString(outChar));
  }else if(drawCommand.startsWith("print(")){
    outChar = drawCommand.substring(5);
    M5.Lcd.print(extractString(outChar));
  }else if(drawCommand.startsWith("setTextSize(")){
    int textSize;
    outChar = drawCommand.substring(11);
    extractString(outChar).trim();
    textSize = extractString(outChar).toInt();
    M5.Lcd.setTextSize(textSize);
  }else if(drawCommand.startsWith("setCursor(")){
    int posiX;
    int posiY;
    String outCharX;
    String outCharY;
    
    outChar = drawCommand.substring(9);
    outChar = extractString(outChar);
    outCharX = outChar.substring(0, outChar.indexOf(","));
    outCharX.trim();
    posiX = outCharX.toInt();
    outCharY = outChar.substring(outChar.indexOf(",") + 1);
    outCharY.trim();
    posiY = outCharY.toInt();
    M5.Lcd.setCursor(posiX, posiY);
  }else if(drawCommand.startsWith("setTextColor(")){
    uint16_t foreColor;
    uint16_t backColor;

    String outCharF;
    String outCharB;
    
    outChar = drawCommand.substring(12);
    outChar = extractString(outChar);
    if(outChar.indexOf(",") >= 0){
      outCharF = outChar.substring(0, outChar.indexOf(","));
      outCharF.trim();
      foreColor = String2Color(outCharF);

      outCharB = outChar.substring(outChar.indexOf(",") + 1);
      outCharB.trim();
      backColor = String2Color(outCharB);
      
      M5.Lcd.setTextColor(foreColor, backColor);
    }else{
      outChar.trim();
      foreColor = String2Color(outChar);
      
      M5.Lcd.setTextColor(foreColor);
    }
  }else if(drawCommand.startsWith("fillScreen(")){
    uint16_t lcdColor = 0;
    outChar = drawCommand.substring(10);
    outChar = extractString(outChar);
    outChar.trim();
    M5.Lcd.fillScreen(String2Color(outChar));
  }
}
