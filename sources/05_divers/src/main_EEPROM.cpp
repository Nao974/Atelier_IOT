#include <Arduino.h>

#include <EEPROM.h>

/* 
 * Exemple de Code afin de stocker des informations
 * en mémoire non volatile à l'image de l'EEPROM d'une Arduino 
 */

// Structure pour stocker les informations
// !!! l'EEPROM est limitée à 512 octets max
struct EEconf {
    char ssid[32];
    char password[64];
    char myhostname[32];
};

// Déclaration de la  variable pour test de relecture
    EEconf readconf;

void setup() {
    Serial.begin(115200);

// Initialisation des données
    EEconf myconf= {
        "SSID_WIFI",
        "phrase2pass",
        "nomHote"
    };

    Serial.print("\nEnregistrement par EEPROM: ");

    EEPROM.begin(sizeof(myconf));
    EEPROM.put(0, myconf);
    EEPROM.commit();

    Serial.println("Fin !");

}

void loop () {
    Serial.println("\n\nRécupération par EEPROM:");
    EEPROM.get(0, readconf);
    Serial.println(readconf.ssid);
    Serial.println(readconf.password);
    Serial.println(readconf.myhostname);

    delay(5000);

}