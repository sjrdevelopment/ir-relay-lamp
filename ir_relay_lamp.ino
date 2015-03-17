/*
  NOTE: This sketch requires a board with an ATMega328 chip.
  Include the IR library from Ken Shirriff at
  http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html
*/
#include <IRremote.h>

int RECV_PIN = 12;
int relayPin = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

String playButtonCode = "e0e0e21d";
boolean isOn = false;

void setup() {
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(relayPin, OUTPUT);   
  digitalWrite(relayPin, LOW); 
}

void loop() {
  if (irrecv.decode(&results)) {
      
    String code = String(results.value, HEX);
    
    if (code == playButtonCode) {
      if (isOn) {
        digitalWrite(relayPin, LOW); 
        isOn = false;
      } else {
        digitalWrite(relayPin, HIGH); 
        isOn = true;
      }
    }
    
    delay(200);
    irrecv.resume(); // Receive the next value
  }
}
