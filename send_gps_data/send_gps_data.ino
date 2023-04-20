#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define rxPin D2
#define txPin D3
#define GPSBaud 9600;

TinyGPSPlus gps;
SoftwareSerial softSer(rxPin, txPin);

HTTPClient http;
WiFiClient client;

double latitude, longitude;
long currentTime, previousTime1, previousTime2;
int ledstatus1, ledstatus2, ledstatus3;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  softSer.begin(9600);
  Serial.println();
  WiFi.begin("Computer1", "1234567890");

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
  }
  Serial.println("done.");
}

// void updateGpsdata() {

//   if (WiFi.status() == WL_CONNECTED) {

//     http.begin(client, "http://192.168.0.102/helping-hand/"); // <1KB payload
//     //  http.begin(client, "http://www.geekstips.com/esp8266-arduino-tutorial-iot-code-example/"); // 30KB payload

//     int httpCode = http.GET();
//     String payload = http.getString();  //Get the response payload

//     Serial.println(httpCode);   //Print HTTP return code
//     Serial.println(payload);    //Print request response payload

//     DynamicJsonDocument doc(200);

//     DeserializationError err = deserializeJson(doc, payload);

//     if (err) {
//       Serial.print(F("deserializeJson() failed with code "));
//       Serial.println(err.f_str());
//     }

//     ledstatus1 = doc["ledstatus1"];
//     ledstatus2 = doc["ledstatus2"];
//     ledstatus3 = doc["ledstatus3"];

//     // Serial.println(ledstatus1);

//     if (ledstatus1) digitalWrite(D5, HIGH);
//     else digitalWrite(D5, LOW);

//     if (ledstatus2) digitalWrite(D6, HIGH);
//     else digitalWrite(D6, LOW);

//     if (ledstatus3) digitalWrite(D7, HIGH);
//     else digitalWrite(D7, LOW);

//     http.end();  //Close connection

//     Serial.printf("Free heap: %d\n", ESP.getFreeHeap());

//   }
// }

void updateGpsdata(double latitude, double longitude) {

  if (WiFi.status() == WL_CONNECTED) {

    http.begin(client, "http://192.168.0.102/helping-hand/update_gpsdata.php");  // <1KB payload
    // http.begin(client, "http://www.geekstips.com/esp8266-arduino-tutorial-iot-code-example/"); // 30KB payload

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "latitude=" + (String)latitude + "&longitude=" + (String)longitude;
    Serial.println(data);

    int httpCode = http.POST(data);
    String payload = http.getString();  //Get the response payload

    // Serial.println(httpCode);   //Print HTTP return code
    // Serial.println(payload);    //Print request response payload
  }
}

void loop() {

  currentTime = millis();

  while (softSer.available() > 0) {
    gps.encode(softSer.read());
    if (gps.location.isUpdated()) {
      // Serial.print("Latitude= ");
      // Serial.print(gps.location.lat(), 6);
      // Serial.print(" Longitude= ");
      // Serial.println(gps.location.lng(), 6);
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }
  }

  if (currentTime - previousTime1 >= 1000) {
    updateGpsdata(latitude, longitude );
    previousTime1 = currentTime;
  }
}