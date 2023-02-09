/* Exemple d'utilisation d'un IOT sur ESP32
    Mettant en pratique l'utilisation d'un serveur Web Asynchrone sur liaison Wifi
        - Stockage des fichiers Web par SPIFFS
        - MAJ des mesures et commande de la LED en AJAX
        
        - ON /OFF d'une led à distance
        - Mesure & Visualisation de la température & Humidité au travers d'un capteur DHT20
    Sur la base du travail de Tommy DesRochers: https://tommydesrochers.com/
*/

#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include "DHT20.h"

const char *SSID = "Livebox...";
const char *PWD= "yez...waeUhtGGTL";
AsyncWebServer server(80);

const uint8_t PINLED = 7;
uint8_t ledState = LOW;

DHT20 DHT;
float humidity, temperature;

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

// Initialisation du gestionnaire de fichier SPIFFS
    Serial.println("Init SPIFFS\n");
    if ( !SPIFFS.begin() ) {
        Serial.println("Erreur SPIFFS...");
        return;
    }
    Serial.println("Fin Init SPIFFS\n");
    
// Connexion au WIFI
    Serial.println("Init Wifi\n"); 
    WiFi.begin(SSID, PWD);
	Serial.print("Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.localIP());

/* Initialisation des différentes page & démarrage du serveur Web 
-------------------------------------------------------------------*/

// Page par défaut à la racine
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

// Chemin pour le css
    server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/w3.css", "text/css");
    });

// Chemin pour le JS
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

// MAJ Temperature
    server.on("/retourtemperature", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        String valeur = String(temperature);
        request->send(200, "text/plain", valeur);
    });

// MAJ Humidité
    server.on("/retourhumidity", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        String valeur = String(humidity);
        request->send(200, "text/plain", valeur);
    });

// Allumage de la LED
    server.on("/ledon", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(PINLED, HIGH);
        request->send(200);
    });

// Extinction de la LED
    server.on("/ledoff", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(PINLED, LOW);
        request->send(200);
    });

// Démarrage du serveur Web 
    server.begin();
    Serial.println("Serveur actif!");
}


void loop() {

    if ( millis() - DHT.lastRead() >= 1000) {
        DHT.read();
        humidity = DHT.getHumidity();
        temperature = DHT.getTemperature();
    }

}

