#include <FlexCAN.h>
#include <kinetis_flexcan.h>

int led = 13;
// create CAN object
;
static CAN_message_t msg;
static CAN_filter_t stm32;
static CAN_filter_t teensy;


void setup() {
  // init CAN bus
  Can0.begin(500000);
  teensy.id = 0x222;
  stm32.id = 0x221;
  pinMode(led, OUTPUT);
  delay(1000);
  Serial.println("CAN Receiver Initialized");
  //Can0.setFilter(stm32, 1);
  //digitalWrite(led, HIGH);

}

void loop() {
  while( Can0.read(msg)) {
    // toggle LEDs
    digitalWrite(led, !digitalRead(led));
    Serial.print("Receiving: ");
    for(int i=0; i<msg.len; i++) {
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
