// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

int incomingByte = 0; // for incoming serial data
int flag = 0; // for flag data
String title = "";
String data = "";

String strUnstable = "Unstable";
String strSuccess = "Success";
String strFailure = "Failure";
String strBuilding = "Building";

void setup() {
  startProgram();
  
  // Green
  pinMode(12, OUTPUT);

  // Yellow
  pinMode(11, OUTPUT);

  // Red
  pinMode(10, OUTPUT);

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '~'){
      beginReadData();
    }
    
    flag = Serial.read();
    if (incomingByte == 'b') {
      data = strSuccess;
      writeDescriptionData();
      green();
    }
    
    else if (incomingByte == 'y') {
      data = strUnstable;
      writeDescriptionData();
      yellow();
    }
    else if (incomingByte == 'r') {
      data = strFailure;
      writeDescriptionData();
      red();
    }
    else if (incomingByte == 'a') {
      data = strBuilding;
      writeDescriptionData();
      turnOffAll();
    }
  }
}

void resetLCD(){
  lcd.clear();
  
  // Write title data
  writeTitleData();
}

void startProgram(){
  // Turn off
  turnOffAll();
  
  // Reset all data on LCD
  resetLCD();
  
  // Write description data
  data = "Ready!!!";
  writeDescriptionData();
}

void beginReadData(){
  // Turn on
  all();
  
  resetLCD();
  
  // Write description data
  data = "Reading data";
  writeDescriptionData();
}

void writeTitleData(){
  title = "My Jenkins ^:^";
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(title);
}

void writeDescriptionData(){
  // Reset all data on LCD
  resetLCD();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print(data);
}

void writeMessageData(){    
    String val="";
    char t;
       
    while(Serial.available() > 0)
    {
      t= Serial.read();
      val=val+t;
      delay(300);
    }
    data = val;
    writeDescriptionData();
    delay(5000);
}

void green() {
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(1000);
}

void yellow() {
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(1000);
}

void red() {
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
}

void all() {
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(1000);
}

void turnOffAll() {
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(1000);
}
