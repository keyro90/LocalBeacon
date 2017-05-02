#include <Arduino.h>

/*
  Struttura Beacon.
  Questo costrutto mi permette di creare una variabile di tipo Beacon e di poter legare
  delle informazioni coerenti.
  Esempio di utilizzo:
  Beacon prova;
  prova.rssi = -23;
  prova.address = "Indirizzo";
*/
typedef struct {
    String address;
    int rssi;
}Beacon;

/*
  Funzione splitString.
  Parametri utilizzati:
  IV : si stringa presa in esame.
  OP : so array che conterrà tutte le stringhe separate.
  OP : leno numero intero che conterrà il numero di stringhe separate.
  IV : term stringa che contiene il separatore di riferimento.
  Esempio di utilizzo:
  String stringa_saluto = "saluto;tutti;come;state?";
  String * ret;
  int nstring = 0;

  splitString(stringa_saluto, ret, &nstring, ";");

  per stampare a video le stringhe:

  for (int i=0; i<nstring; i++){
    Serial.println(ret[i]);
  }

*/
void splitString(const String& si, String * so, uint16_t * leno, const String term = "\r\n"){
    uint16_t i = 0, ns = 0;
    so[ns] = "";
    while (i < si.length()){
        bool is_term = true;
        if (term == "")
            is_term = false;
        else{
            for (uint16_t k = 0; k<term.length(); k++){
                if (si.charAt(i+k) != term.charAt(k)){
                    is_term = false;
                    break;
                }//if
            }//for-term
        }//else
        if (is_term){
            so[++ns] = "";
            i += term.length();
        }//if-si
        else
            so[ns] += (char)si[i++];
    }//while
    if (i == si.length() && so[ns] != "")
        ns++;
    (*leno) = ns;
}//splitString

/*
  Funzione che converte una stringa esadecimale in numero.
  Il secondo parametro è la lunghezza della Stringa.
  Esempio:
  int hex_number = conv_hex_to_dec("FF344", 5);

*/
int conv_hex_to_dec(const String shex, const unsigned int len){
  int res = 0;
  for (unsigned int i = 0; i<len; i++)
    res = res << 4 | ((shex[i] >= '0' && shex[i] <= '9') ? (shex[i] - '0') : (shex[i] - 'A' + 10));
  return res;
}//conv_hex_to_dec

/*
  Funzione is_in_array.
  Questa funzione, dato un indirizzo, un array di Beacon e la lunghezza, dice se l'indirizzo è già presente con un booleano.
*/
bool is_in_array(Beacon *list, uint16_t len, String tofind){
    for (uint16_t i=0; i<len; i++)
        if (list[i].address == tofind)
            return true;
    return false;
}//is_inArray
