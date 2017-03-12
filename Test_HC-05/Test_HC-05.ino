/*
  Test_HC-05.ino
  Il programma testa il funzionamento del modulo
  Bluetooth tipo HC-05

  Sono utilizzati i seguenti pin
  Pin +3.3V         -> Alimentazione modulo HC-05
  Pin GND           -> GND modulo HC-05
  Pin Digital 9     -> Abilita modalità Command AT
  Pin Digital 10    -> RX HC-05
  Pin Digital 11    -> TX HC-05

  Creato il 08/01/2017 da Adriano Gandolfo
  Sito web http://www.adrirobot.it
  Blog http://it.emcelettronica.com/author/adrirobot
  Pagina Facebook https://www.facebook.com/Adrirobot-318949048122955
  Istagram https://www.instagram.com/adrirobot/
  This example code is in the public domain.
*/

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  pinMode(9, OUTPUT);  // questo pin è connesso al relativo pin 34 (pin KEY) del HC-05
  // che portato a HIGH permette di passare alla modalità AT
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Inserire i comandi AT:");
  BTSerial.begin(38400);  // Velocità di default del modulo HC-05
}

void loop()
{
  // Continua a leggere da HC-05 e invia Serial Monitor Arduino
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Continua a leggere da Arduino Serial Monitor e invia a HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}


