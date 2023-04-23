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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  softSer.begin(9600);
  Serial.println();
  WiFi.begin("D&DC", "qwertzui");

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
  }
  Serial.println("done.");
}

void updateGpsdata(double latitude, double longitude) {

  if (WiFi.status() == WL_CONNECTED) {

    http.begin(client, "http://192.168.197.1/helping-hand/update_gpsdata.php");  // <1KB payload
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