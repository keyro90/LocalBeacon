#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX  

const int rxpin = 11;
const int txpin = 10;
SoftwareSerial bluetooth(rxpin, txpin);
char  cara;
char  caro;
// String  cara;
unsigned long Ttrascorso=0;
unsigned long Tinizio=0;
unsigned long Tattuale=0;
String stringhe_lette[100];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  bluetooth.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");

//  bluetooth.println("Hello, world?");
}


void loop() { 

  if (bluetooth.available()) {
//    Serial.write(bluetooth.read());
//    String caro = bluetooth.readString();
    caro = bluetooth.read();
//    if(cara='OK') { 
//      Serial.print("completato: "); 
//      Serial.println(cara);
//    }
    Serial.print("caro  ");
    Serial.println(caro);
   }
  if (Serial.available()) {
//      bluetooth.write(Serial.read());
      cara = Serial.read();
//      Serial.print("prima");
//      Serial.println(cara);
      bluetooth.write(cara);
//      Serial.write(cara);
      Serial.println(cara);
  }      

}

