#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "DHT20.h"
DHT20 DHT;
const uint8_t PINLED = 7;

// Définition des paramétrages de connexion Wifi & MQTT
const char *SSID = "Livebox-A250";
const char *PWD= "yezvypYswaeUhtGGTL";
const char *HOSTNAME = "ESP32C3M1";
//const char * mqtt_server = "broker974.local";
const char * mqtt_server = "192.168.1.27";
const char * mqtt_user = "nao974";
const char * mqtt_passwd = "az$er";

WiFiClient espClient;
PubSubClient client(espClient);
uint32_t lastMillis = 0; // Pour la gestion de la temporisation d'envoi des topics

// Fonction appelée lors de la reception d'un topic
// Les paramétres sont imposés par la librairie MQTT
void callback(char* topic, uint8_t* payload, uint16_t length) {
// Affichage du topic reçu    
    Serial.print("Message [");
    Serial.print(topic);
    Serial.print("] ");
// Affichage du payload (la donnée reçue)    
    for (uint16_t i = 0; i< length; i++)
        Serial.print((char) payload[i]);
    Serial.println();

// Le 1er caratère est "1" => Allumage de la LED
    if ( (char)payload[0] == '1' )   
        digitalWrite(PINLED, HIGH);
    else 
        digitalWrite(PINLED, LOW);
}

// Fonction de (re)connexion au serveur MQTT
// Et abonnement au topic ctrlled
void reconnect() {
// Connecté au Broker ?    
    while( !client.connected() ) {
// Si non, on se connecte        
        if ( !client.connect(HOSTNAME,mqtt_user, mqtt_passwd) ) {
            Serial.print("Erreur connexion MQTT, rc=");
            Serial.println(client.state() );
            delay(5000);
            continue;
        }
    Serial.println("Connexion serveur MQTT ok");
// Connecté, on s'abonne au topic "ctrlled"
    client.subscribe("ctrlled");
    }
}

void setup() {
// Debug console
    Serial.begin(115200);

// Connexion Wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PWD);
    Serial.print("\n\nTentative de connexion...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("\n");
    Serial.println("Connexion Wifi etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("");

// Initialisation de la broche de la LED
    pinMode(PINLED, OUTPUT);
    digitalWrite(PINLED, LOW);

// Initialisation du capteur d'humidité & Température
    DHT.begin(2, 3); // DataPin, ClockPin

// Configuration du Broker
    client.setServer(mqtt_server, 1883);
// Configuration du callBack
    client.setCallback(callback);
}

void loop() {
// array pour les données des messages à envoyer
    char msg[16];
// array pour le nom du topic à envoyer
    char topic[64];

// sommes nous connectés ?
    if (!client.connected() )
        reconnect();

// gestion MQTT
    client.loop();

// Temporisation
    if ( millis() - lastMillis > 5000) {
        lastMillis = millis();

// Lecture du capteur
        DHT.read();
// Construction du message        
        sprintf(msg, "%f", DHT.getTemperature());
// Construction du nom du topic        
        sprintf(topic, "maison/%s/temperature", HOSTNAME);
// Publication        
        client.publish(topic, msg);

// Idem pour l'humidity     
        sprintf(msg, "%f", DHT.getHumidity());
// Construction du nom du topic        
        sprintf(topic, "maison/%s/humidity", HOSTNAME);
// Publication        
        client.publish(topic, msg);        
    }
}
