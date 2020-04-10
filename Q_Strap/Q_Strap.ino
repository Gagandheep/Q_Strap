 #include <ESP8266WiFi.h>
 
const char* ssid = "Sticker_01";
const char* password = "1234pass";

void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  WiFi.begin(ssid, password); 
}

void loop() {
  delay(2000);
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("connected");
    Serial.println("going deep sleep for 5 sec");
    ESP.deepSleep(5e6);
  }
  else{
    digitalWrite (5,HIGH);
    delay(500);
    digitalWrite(5,LOW); 
    Serial.println("not connected");
    delay(500);
  }
}
