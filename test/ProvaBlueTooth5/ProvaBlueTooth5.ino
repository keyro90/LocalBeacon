#include <SoftwareSerial.h>
// SoftwareSerial mySerial(10, 11); // RX, TX  

// char richiesta;
const int rxpin = 10;
const int txpin = 11;
SoftwareSerial bluetooth(rxpin, txpin);
char volta="X";
char rispostaArray[100];
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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  Serial.println("Resetto...");
  Serial.println(getRisposta("AT+RESET\r\n"));

}

void loop() { 
  if(volta!='A')  {
    Serial.println("prima volta");
    primaVolta();
    volta='A';  
  } else {
    Serial.println("seconda volta");
    secondaVolta();
  }
}

void primaVolta() {    // comandi apertura modalità AT + INQuiry 
      Serial.print("AT: ");
      Serial.println(getRisposta("AT\r\n"));
      Serial.print("AT+Role=1: ");
      Serial.println(getRisposta("AT+ROLE=1\r\n"));
      Serial.print("AT+INIT: ");
      Serial.println(getRisposta("AT+INIT\r\n"));
      Serial.print("AT+INQM: ");
      Serial.println(getRisposta("AT+INQM=1,3,15\r\n"));
      Serial.print("AT+INQ: ");
      String rilevati = getRisposta("AT+INQ\r\n");
      Serial.print("rilevati: ");
      Serial.println(rilevati);
      //si divide la stringa per ottenere id e rssi.
      Scompattamento(rilevati);
      delay(20000);
//      Serial.println("Resetto...");
//      Serial.println(getRisposta("AT+RESET\r\n"));
}

void secondaVolta() { 
      bluetooth.write("AT+INQ\r\n");   // ricerca dispositivi bluetoooth
      String rilevati = getRisposta("AT+INQ\r\n");
      Serial.print("rilevati: ");
      Serial.println(rilevati);
      //si divide la stringa per ottenere id e rssi.
      Scompattamento(rilevati);
      delay(20000);
//      Serial.println("Resetto...");
//      Serial.println(getRisposta("AT+RESET\r\n"));
//      comando('Q');          // riceve le risposte dal modulo
}

String getRisposta(const char * comando_inviato){
  bluetooth.write(comando_inviato);
  return bluetooth.readString();
}

String Scompattamento(String rilevato){
  unsigned int stop = 0;
  unsigned int z=0;

// inserire qui la rilevazione della lunghezza di stringa
  char buff[100];
  rilevato.toCharArray(buff,100);
  calcolaLunghezza(buff);

  while(stop=0) {
    unsigned int x=4; unsigned int y=0; unsigned int g=0;
    while(rilevato[x] != "/r") {
      rispostaArray[y]=rilevato[x];
      x++; y++;
    } // while rilevato[]        
    if(risposta="OK") {  stop=1;
    } else{ risposteM[z]=risposta;  
            z++;
    }
  } // while stop=0 

//   return P1 P2 P3;
}
void calcolaLunghezza(char *st) {
  int lung = 0;
  while( *st++ )
  ++lung ;
  Serial.print(lung);
  Serial.print(" lunghezza stringa, ");
  Serial.print("Scompattamento,rilevato: ");
  Serial.println(st);
}

