 /*
 * Team Id: 238
 * Author List:  Adarsh, Bhargav, Gagandheep, Yasho Mangal
 * Filename: Q_Strap
 * Functions: setup , loop
 * Global Variables: ssid, password
 */

// Library imports
 #include <ESP8266WiFi.h>

 #define PIN_BUZZER 5                   // pin to which buzzer is connected
  
const char* ssid = "Sticker_01";        // SSID
const char* password = "1234pass";      // password


 /*
 * Function Name: setup
 * Input: None
 * Output: None
 * Description: arduino setup function
 */

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);        // set pin 5 as Output
  WiFi.begin(ssid, password);         // connect to Sticker

  delay(2000);
}

/*
 * Function Name: loop
 * Input: None
 * Output: None
 * Description: arduino loop function
 */

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    ESP.deepSleep(5e6);               // deepSleep for 5 seconds
  }
  else{                               // Beep buzzer continuously
    digitalWrite (PIN_BUZZER, HIGH);  // set buzzer pin to HIGH
    delay(500);
    digitalWrite(PIN_BUZZER, LOW);    // set buzzer pin to LOW
    delay(500);
  }
}
