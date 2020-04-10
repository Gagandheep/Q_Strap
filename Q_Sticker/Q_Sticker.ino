 /*
 * Team Id: 238
 * Author List:  Adarsh, Bhargav, Gagandheep, Yasho Mangal
 * Filename: Q_Sticker
 * Functions: send_message, setup , loop
 * Global Variables: Q_num, contacts, time_secs, reported, ssid, password
 */

// Library imports
#include <ESP8266WiFi.h>

#define NOS 2                         // constant to hold the number of contacts to which alert has to be sent
#define NORMAL_CHECK_DELAY 12e7       // time (us) delay between connection checks when all straps are connected
#define CRITICAL_CHECK_DELAY 5000     // time (ms) delay between connection checks when all straps are not connected
#define MAX_OFFLINE_DURATION 10000    // time (ms) duration during which the sticker waits for the straps to reconnect if Disconnected, after which an alert is sent
#define PIN_BUZZER 5                  // pin to which buzzer is connected

int Q_num = 1;                                                        // number of straps to be connected
String contacts[NOS] = { "\"+910000000000\"", "\"+910123456789\""};   // list of contacts
unsigned long time_secs = 0;                                          // variable to measure strap offline durartion
bool reported = false;                                                // true if message is sent
const char* ssid = "Sticker_01";                                      // SSID
const char* password = "1234pass";                                    // password

 /*
 * Function Name: send_message
 * Input: None
 * Output: None
 * Description: Sends text message to the phone numbers present in the list 'contacts' 
 * Example Call: send_message();
 */

void send_message() {
  for (int i = 0; i < NOS; i++) {
    Serial.println();
    Serial.println("AT+CMGF=1");  // Set GSM in text mode
    delay(1000);                  // One second delay
    Serial.println();
    Serial.print("AT+CMGS=");     // Enters the receiver number
    Serial.print(contacts[i]);
    Serial.println();
    delay(100);
    Serial.print("Disconnected"); // SMS body
    delay(1000);
    Serial.println();
    Serial.write(26);             // Send Text
  }
}

 /*
 * Function Name: setup
 * Input: None
 * Output: None
 * Description: arduino setup function
 */

void setup() {

  Serial.begin(9600);                             // Begin nodemcu serial-0 channel
  pinMode(PIN_BUZZER, OUTPUT);                    // Set buzzer pin as output

  boolean result = WiFi.softAP(ssid, password);   // Setup nodemcu in softAP mode
  if (result == true)                             // if setup was successful
  {
    Serial.print("AT");                           //Start Configuring GSM Module
    delay(10000);

  }
  else
  {
    digitalWrite (PIN_BUZZER, HIGH);              // Set buzzer pin to HIGH
  }
}

 /*
 * Function Name: loop
 * Input: None
 * Output: None
 * Description: arduino loop function
 */

void loop() {
  
  if(WiFi.softAPgetStationNum() == Q_num){        // Check whether all straps are conneted
    ESP.deepSleep(NORMAL_CHECK_DELAY);            // deepSleep if all straps are connected
  }

  while (WiFi.softAPgetStationNum() != Q_num) {   // while any of the straps is disconnected
    delay(CRITICAL_CHECK_DELAY); 
    time_secs += CRITICAL_CHECK_DELAY;
    if (time_secs >= MAX_OFFLINE_DURATION && !reported) {
      send_message();                             // Report
      reported = true;
      while (WiFi.softAPgetStationNum() != Q_num) {   // Beep Buzzer continuously until all straps reconnect
        digitalWrite (PIN_BUZZER, HIGH);
        delay(500);
        digitalWrite(PIN_BUZZER, LOW);
        delay(500);
      }
    }
  }
  time_secs = 0;
  reported = false;
}
