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
      Serial.println(rilevati);
      delay(1000);
      Serial.println("Resetto...");
      Serial.println(getRisposta("AT+RESET\r\n"));
      
}
void secondaVolta() { 
      bluetooth.write("AT+INQ\r\n");   // ricerca dispositivi bluetoooth
      comando('Q');          // riceve le risposte dal modulo
}
//-------------------------------------------
void comando(char scans) {     // scansione le risposte da bluetooth
  String risposteM[100];
  Ttrascorso=0;
  Tinizio = millis();
  //delay(15);
  risposta = bluetooth.readString();  
      Serial.print("inizio, risposta: ");   Serial.print(risposta);
      Serial.println("");
  risposteM[0] = risposta;
  unsigned int i=1;
//  scansiona fino ad incontrare OK o fino al limite di tempo
  while(risposta != "OK" && Ttrascorso < 5000) {
  risposta = bluetooth.readString();
      Serial.print("loop while: ");     Serial.print(i);
      Serial.print(", durata: ");       Serial.print(Ttrascorso);
      Serial.print(", risposta: ");     Serial.print(risposta);
      Serial.println("");
  if(risposta != ' ')   {    // non memorizza se risposta vuota
    risposteM[i] = risposta; // memorizza risposta
    i++;
  }
    Tattuale = millis();
    Ttrascorso = Tattuale-Tinizio;  // determina il tempo di scansione
  } //while
  unsigned int n_risposte = i;
  if(scans == 'Q') {                // scansiona solo se AT+INQ
    for(int j=0; j<n_risposte; j++) {
// qui inserisco algoritmo per prelevare nome dispositivo e potenza segnale
//    char *t;
    char *p1;
    char *p2;
    char *p3;
    char buf[100];
//    risposta.toCharArray(buf,100);
    risposteM[j].toCharArray(buf,100);
/*
    Serial.print("convertita: ");
    Serial.print(risposteM[j]);
    Serial.print(", buf: ");
    Serial.println(buf);
*/
    p1= strtok(buf, ",");
    p2= strtok(NULL, ",");
    p3= strtok(NULL, ",");
/*
    Serial.print("parametro 1: ");
    Serial.print(p1);
    Serial.print(", parametro 2: ");
    Serial.print(p2);
    Serial.print(", parametro 3: ");
    Serial.println(p3);
*/
    //delay(1000);
    }
  }
}

String getRisposta(const char * comando_inviato){
  bluetooth.write(comando_inviato);
  return bluetooth.readString();
}





