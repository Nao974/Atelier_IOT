#include <Arduino.h>

/* 
 * Exemple de Code pour la mise en oeuvre du DeepSleep sur ESP32
 * Pendant ce mode la majeure partie de la RAM et tous les périphériques numériques sont mis hors tension. 
 * Les seules parties de la puce qui restent sous tension sont les suivantes :
 *    - Contrôleur RTC
 *    - Périphériques RTC 
 *        - le processeur ULP
 *        - Mémoires RTC (lentes et rapides)
 */

// Pour sauvegarder une variable même après avoir mis l'ESP en deep sleep
//  il faut l'enregistrer dans la mémoire RTC en déclarant la variable en globale de ce type
RTC_DATA_ATTR int bootCount = 0;


const uint32_t uS_TO_S_FACTOR = 1000000; // facteur de conversion de µs vers seconde
const uint8_t TIME_TO_SLEEP   = 3;       // Temps en seconde passé en mode deep sleeep

const uint8_t GREEN_LED_PIN  = 25;
const uint8_t YELLOW_LED_PIN = 26;

void setup() {

    pinMode(GREEN_LED_PIN,OUTPUT);
    pinMode(YELLOW_LED_PIN,OUTPUT);
    delay(500);
    
// Contrairement au mode light sleep, 
//  la carte redémarre à chaque réveil et effectue donc à nouveau le setup 

// A faire qu'au 1er démarrage  
    if (bootCount == 0) { 
        digitalWrite(YELLOW_LED_PIN,HIGH);
        bootCount = bootCount+1;
    } 
// Pour les autres démarrages issus du reveil    
    else  {
        digitalWrite(GREEN_LED_PIN,HIGH);
    }
    
    delay(3000);

    digitalWrite(GREEN_LED_PIN,LOW);
    digitalWrite(YELLOW_LED_PIN,LOW);

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
}

void loop() {
 
}