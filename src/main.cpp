#include <FlexCAN.h>
#include <kinetis_flexcan.h>
/*
Base pour la reception de trame sur le bus CAN, code fonctionnel pour Teensy 3.2
Pas besoin d'installer de librairie la librairie FlexCAN.h (collin80 fork sur GHUb) est dans Teensyduino.
Si questions, voir P.A (kingovchouffe sur github) ou mail au pierre.anthony.legeay@gmail.com
*/
int led = 13;
// create CAN object
;
// définition du message à recevoir
static CAN_message_t msg;

//Définition des filtes
static CAN_filter_t stm32;
static CAN_filter_t teensy;


void setup() {
  // initialisation du bus CAN, le baudrate est en paramètre, pas besoin de mettre de filtre ici.
  // 500kbps ok suffisant pour les tests à voir en conditions réelles.(ESSENTIEL)
  Can0.begin(500000);
  // définition des filtres pour les différents messages à modifier selon les id des messsags sur le bus
  // Pas besoin d'utiliser la fonction setfilter de la lib car cela bloque le controller sur un type de message
  teensy.id = 0x222;
  stm32.id = 0x221;
  pinMode(led, OUTPUT);
  delay(1000);
  Serial.println("CAN Receiver Initialized");


}

void loop() {
  // la fonction read renvoie 1 quand un message arrive dans le buffer du controlleur CAN
  while( Can0.read(msg)) {
    // clignotage LEDs très pratique ;)
    digitalWrite(led, !digitalRead(led));
    Serial.print("Receiving: ");
    for(int i=0; i<msg.len; i++) {
      //Condition if pour choisir l'id que l'on veut recevoir
      //if(msg.id==stm32.id)
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    //delay(500);
    /*for(int i=0; i<msg.len; i++) {
      //if(msg.id==teensy.id)
      Serial.print(msg.buf[i]); Serial.print(" ");
    }*/
    Serial.println("");
  }
}
