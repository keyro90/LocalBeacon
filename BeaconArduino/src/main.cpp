#include <Arduino.h>
#include "utility.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#define ID_DEVICE "0"
#define OFFSET 10

ESP8266WiFiMulti WiFiMulti;
const int rxpin = 13;
const int txpin = 15;

SoftwareSerial bluetooth(rxpin, txpin, false, 256);

/*
  Funzione getRisposta.
  Parametri:
  IP : comando_inviato comanda da inviare al modulo bluetooth.
  IV : max_ms tempo in millisecondi di timeout per attendere la risposta del bluetooth.
  OR : ritorna una stringa con la risposta. Nel caso peggiore, ritornerà vuota.
*/
inline String getRisposta(const char * comando_inviato, unsigned long max_ms = 1000){
  String s;
  bluetooth.setTimeout(max_ms);
  bluetooth.flush(); //Meglio svuotare il canale di comunicazione prima di inviare qualcosa.
  bluetooth.write(comando_inviato);
  int time = millis();
  while(!bluetooth && millis()-time < 100) time = millis(); //Questo ciclo mi permette di evitare attese infinite.
  s = bluetooth.readString();
  return s;
} // getRisposta

/*
  Funzione per mandare una stringa all'indirizzo IP assegnato al Server.
*/
void sendJson(String json){
    const uint16_t port = 8888;
    const char * host = "192.168.1.215"; // ip or dns
    WiFiClient client;

    if (!client.connect(host, port)) {
        delay(500);
        return;
    }
    client.print(json);
}

/*
  Funzione scanRilevati.
  Parametri:
  IV : lista di stringhe contenente le stringhe ottenute con l'inquiring.
  IV : lunghezza dell'array.
  Questa funzione si divide in due parti:

  1) Scansiona ogni elemento dell'array di stringhe ed elimina i duplicati.
  2) Compone il JSON da inviare al Server.
  3) Chiama la funzione per inviare il JSON al Server.
*/
void scanRilevati(const String *list, int length){
    int m = 0;
    Beacon detectedBeacon[5];
    //Parte la scansione delle stringhe
    for (int i=0; i<length; i++){
        String param[3];
        uint16_t n_param = 3;
        splitString(list[i], param, &n_param, ",");
        //param contiene i parametri separati dalla virgola.
        String address = param[0].substring(5);
        if (!is_in_array(detectedBeacon, m, address)){ //se l'indirizzo del beacon non è presente nell'array allora lo aggiungo, con il suo relativo rssi.
            detectedBeacon[m].address = address;
            int dbm = conv_hex_to_dec(String(param[2][0])+String(param[2][1])+String(param[2][2])+String(param[2][3]), 4); //Converto in decimale l'RSSI.
            detectedBeacon[m].rssi =  -((dbm ^ 0xffff) - OFFSET ) ; //Complemento a due dei bit per ottenere il numero.
            m++;
        }//if
    }//for

    //Compongo il JSON.
    String json = "{\"id\" : "+String(ID_DEVICE)+", \"beacon\" : {";
    if (m > 1){
        json += " \""+detectedBeacon[0].address+"\" : "+String(detectedBeacon[0].rssi)+"";
        for (int i=1; i<m; i++){
            json += ", \""+detectedBeacon[i].address+"\" : "+String(detectedBeacon[i].rssi)+"";
        }//for
    }//if-
    json += " }}";
    sendJson(json);
}//scanRilevati

void setup() {
  Serial.begin(115200);
  bluetooth.begin(38400);
  bool is_init = false;
  String risp;
  Serial.println("Starting...");
  //Finchè non rilevo OK dal comando AT+INIT rimango nel setup e riprovo.
  while(!is_init){
      Serial.println("Inizializzo...");
      getRisposta("AT+RESET\r\n");
      getRisposta("AT\r\n");
      risp = getRisposta("AT+INIT\r\n");
      getRisposta("AT+ROLE=1\r\n");
      getRisposta("AT+INQM=1,10,30\r\n");
      if (risp == "OK\r\n")
        is_init = true;
      else
        Serial.println("...Modalita AT non riuscita");
  }//while
  Serial.println("...Pronto");

  WiFiMulti.addAP("", "");//Inserire nome della Rete Wifi e Password.

  while(WiFiMulti.run() != WL_CONNECTED) { //Finchè non sono collegato alla rete WiFi non proseguo.
      Serial.print(".");
      delay(500);
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

}  //setup

void loop() {
    /*Lancio il comando di inquiring e prendo la risposta.
      Attenzione che la risposta è continua, io rilevo le stringhe
      ogni 3 secondi e le valuto.
      Quindi non aspetto che il comando finisca.
    */
    String rilevati = getRisposta("AT+INQ\r\n", 3000);
    String list_string[10];
    uint16_t len = 0;
    splitString(rilevati, list_string, &len, "\r\n");//spezzo la stringa.
    if (len > 0){
        String list_inq[10];
      int m = 0;
      for (uint16_t i=0; i<len; i++){ //Elimino le righe che non iniziano per "+".
        if (list_string[i][0] == '+')
            list_inq[m++] = list_string[i];
      }//for
      //m mi dice quante sono le righe con il "+". Se ce ne sono...
      if (m > 0)
        scanRilevati(list_inq, m);
    }//if-len
} // loop
