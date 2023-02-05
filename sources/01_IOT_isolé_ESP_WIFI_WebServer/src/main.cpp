/* Exemple d'utilisation d'un IOT sur ESP32
    Mettant en pratique l'utilisation d'un serveur Web sur liaison Wifi
        - ON /OFF d'une led à distance
        - Mesure & Visualisation de la température & Humidité au travers d'un capteur DHT20
    Sur la base du travail de Tommy DesRochers: https://tommydesrochers.com/
*/

#include <Arduino.h>

#include <WiFi.h>
#include <mDNS.h>

#include "DHT20.h"

const char *SSID = "Livebox-A250";
const char *PWD= "yezvypYswaeUhtGGTL";

const uint8_t PINLED = 7;
uint8_t ledState = LOW;

DHT20 DHT;
float humidity, temperature;

void handleRoot() {
    String page = "<!DOCTYPE html>";

    page += "<html lang='fr'>";
    page += "<head>";
    page += "    <title>Serveur ESP32</title>";
    page += "    <meta http-equiv='refresh' content='5' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8' />";
    page += "    <link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";
    page += "</head>";

    page += "<body>";

    page += "    <div class='w3-card w3-blue w3-padding-small w3-jumbo w3-center'>";
    page += "        <p>Commande LED</p>";
    page += "    </div>";

    page += "    <div class='w3-bar'>";
    page += "        <a href='/ledon' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>ON</a>";
    page += "        <a href='/ledoff' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>OFF</a>";
    page += "    </div>";

    page += "    <div class='w3-card w3-green w3-padding-small w3-jumbo w3-center'>";
    page += "        <p>Valeur des Capteurs</p>";
    page += "    </div>";

    page += "    <div class='w3-center w3-padding-16 w3-jumbo'>";
    page += "       <p>Température: "; page += temperature; page += " °C</p>";
    page += "       <p>Humidité: "; page += humidity; page += " %</p>";
    page += "    </div>";

    page += "</body>";
    page += "</html>";

    server.setContentLength(page.length());
    server.send(200, "text/html", page);
}

void handleNotFound() {
    server.send(404, "text/plain", "404: Not found");
}

void handleLedOn() {
    digitalWrite(PINLED, ledState = HIGH);
    server.sendHeader("Location","/");
    server.send(303);
}

void handleLedOff() {
    digitalWrite(PINLED, ledState = LOW);
    server.sendHeader("Location","/");
    server.send(303);
}

void setup() {
// Initialisation de la liaison série
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n");

// Initialisation de la broche de la LED
    pinMode(PINLED, OUTPUT);
    digitalWrite(PINLED, ledState);

// Initialisation du capteur d'humidité & Température
    DHT.begin(2, 3); // DataPin, ClockPin

// Connexion au WIFI    
    WiFi.persistent(false);
    WiFi.begin(SSID, PWD);
    Serial.print("Tentative de connexion...");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\n");
    Serial.println("Connexion etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

// Initialisation des différentes page & démarrage du serveur Web 
    server.on("/", handleRoot);
    server.on("/ledon", handleLedOn);
    server.on("/ledoff", handleLedOff);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Serveur web actif!");
}

void loop() {

// Lecture du capteur toutes les 1 seconde(s) (1000 ms)
    if ( millis() - DHT.lastRead() >= 1000) {
        DHT.read();
        humidity = DHT.getHumidity();
        temperature = DHT.getTemperature();

        /* Serial.print("Humidity: ");
        Serial.print(humidity, 1);
        Serial.print(" %\t\tTemperature ");
        Serial.print(temperature, 1);
        Serial.println("°C"); */
    }   

// Detection des nouvelles requetes sur le serveur Web et MAJ-Envoi des pages
    server.handleClient();

}
