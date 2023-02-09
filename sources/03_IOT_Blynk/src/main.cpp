#include <Arduino.h>
/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_TEMPLATE_ID           "TMPLxiv21b68"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "pfgkTzg...G6k-1o55je5BDP"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Livebox...";
char pass[] = "yezv...waeUhtGGTL";

BlynkTimer timer;

#include "DHT20.h"
DHT20 DHT;
const uint8_t PINLED = 7;

// This function is called every time the Virtual Pin 7 state changes
BLYNK_WRITE(7) {
    int value = param.asInt();
    digitalWrite(PINLED, value);
    // Update state
    Blynk.virtualWrite(V0, param);
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void myDHT20Event() {

        DHT.read();
        Blynk.virtualWrite(V4, DHT.getTemperature());
        Blynk.virtualWrite(V5, DHT.getHumidity());
}

void setup() {
    // Debug console
    Serial.begin(115200);

    Blynk.begin(auth, ssid, pass);

// Initialisation de la broche de la LED
    pinMode(PINLED, OUTPUT);
    digitalWrite(PINLED, LOW);

// Initialisation du capteur d'humidité & Température
    DHT.begin(2, 3); // DataPin, ClockPin

    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
    timer.setInterval(2000L, myDHT20Event);
}

void loop() {
    Blynk.run();
    timer.run();
}
