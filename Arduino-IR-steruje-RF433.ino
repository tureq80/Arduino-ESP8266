/*
Pomysł na sterowanie pilotem urządzeniami RF433Mhz potrzebny jest nadajnik RF433Mhz oraz Czytnik IR
*/

#include <RCSwitch.h> 
RCSwitch mySwitch = RCSwitch();
#include <IRremote.h>

int RECV_PIN = 3; // IR pin

#define code1 3305 // stop sony
#define code2 21336 // title sony
#define code3 0000 // 3

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
Serial.begin(9600); // konsola
irrecv.enableIRIn(); // IR 
mySwitch.enableTransmit(10);  // declare PIN RF modul

}
void loop() {
if (irrecv.decode(&results)) {
unsigned int value = results.value;
switch(value) {

  
case code1:
//włącz światło po RF433Mhz 
mySwitch.sendTriState("FFF11FF0FFF0");
break;


case code2:
//wyłącz światło po RF433Mhz 
mySwitch.sendTriState("FFF11FF0FF0F");

break;


case code3:

// brak pomyslu

break;
}
Serial.println(value); 
irrecv.resume(); 
}
}
