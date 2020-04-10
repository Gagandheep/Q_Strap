#include <ESP8266WiFi.h>

#define NOS 2
#define NORMAL_CHECK_DELAY 12000
#define CRITICAL_CHECK_DELAY 5000
#define MAX_OFFLINE_DURATION 10000

int Q_num = 1;
String contacts[NOS] = { "\"+910000000000\"", "\"+910123456789\""};
unsigned long time_secs = 0;
bool reported = false;

void send_message() {
  for (int i = 0; i < NOS; i++) {
    Serial.println();
    Serial.println("AT+CMGF=1");  // Set GSM in text mode
    delay(1000);                  // One second delay
    Serial.println();
    Serial.print("AT+CMGS=");     // Enter the receiver number
    Serial.print(contacts[i]);
    Serial.println();
    delay(100);
    Serial.print("Disconnected"); // SMS body - Sms Text
    delay(1000);
    Serial.println();
    Serial.write(26);
  }
}

void setup() {
  //Begin nodemcu serial-0 channel
  Serial.begin(9600);
  pinMode(5, OUTPUT);

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("Sticker_01", "1234pass");
  if (result == true)
  {
    Serial.println("Ready");
    Serial.print("AT");  //Start Configuring GSM Module
    delay(10000);

  }
  else
  {
    Serial.println("Failed!");
  }
}

void loop() {
  
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  if(WiFi.softAPgetStationNum() == Q_num){
    Serial.println("ESP going to deep sleep for required checking time");
    Serial.println();
    delay(10000);
    ESP.deepSleep(2e7);
  }
  //delay(NORMAL_CHECK_DELAY);
  while (WiFi.softAPgetStationNum() != Q_num) {
    Serial.println("checking connection again");
    delay(CRITICAL_CHECK_DELAY);
    time_secs += CRITICAL_CHECK_DELAY;
    if (time_secs >= MAX_OFFLINE_DURATION && !reported) {
      send_message();
      reported = true;
      while (WiFi.softAPgetStationNum() != Q_num) {
        digitalWrite (5, HIGH);
        delay(500);
        digitalWrite(5, LOW);
        delay(500);
      }
    }
  }
  time_secs = 0;
  reported = false;
}
