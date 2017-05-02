#include <SoftwareSerial.h>
// SoftwareSerial mySerial(10, 11); // RX, TX  

// char richiesta;
const int rxpin = 10;
const int txpin = 11;
SoftwareSerial bluetooth(rxpin, txpin);
char volta="X";
String risposta;
String risposteM[100];
unsigned long Ttrascorso=0;
unsigned long Tinizio=0;
unsigned long Tattuale=0;
//String stringhe_lette[100];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  bluetooth.begin(38400);
//  bluetooth.begin(4800);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");

//  bluetooth.println("Hello, world?");

}

void loop() { 
  if(volta!='A')  {
    Serial.println("prima volta");
    primaVolta();
    volta='A';  
  } else {
//    Serial.println("seconda volta");
//    secondaVolta();
  }
}

void primaVolta() {    // comandi apertura modalità AT + INQuiry 
      Serial.println(getRisposta("AT\r\n"));
      Serial.println(getRisposta("AT+ROLE=1\r\n"));
      Serial.println(getRisposta("AT+INIT\r\n"));
      Serial.println(getRisposta("AT+INQM=1,3,15\r\n"));
      String rilevati = getRisposta("AT+INQ\r\n");
      //si divide la stringa per ottenere id e rssi.
      //dividilinea(...)
      Serial.println(rilevati);
      delay(1000);
      Serial.println("Resetto...");
      Serial.println(getRisposta("AT+RESET\r\n"));
      
}

String getRisposta(const char * comando_inviato){
  bluetooth.write(comando_inviato);
  return bluetooth.readString();
}




