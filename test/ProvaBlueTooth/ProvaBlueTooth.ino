#include <SoftwareSerial.h>
<<<<<<< HEAD
SoftwareSerial mySerial(10, 11); // RX, TX  
    int boud = 9600;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(boud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(boud);
  mySerial.println("Hello, world?");
}
void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
//    Serial.println("");
//    char c = (mySerial.read());
//    Serial.print("qui ");
//    Serial.write(c);
//    Serial.println("");
//    Serial.print(mySerial.read());
//    Serial.println("");
  }    
//    char buf[6]= "      ";
//    char r = 'a';
//    int  pos = 0;
  if (Serial.available()) {
    mySerial.write(Serial.read());
//    while(pos<7) {
//      r = Serial.read();
//      buf[pos] = r;
//      pos = pos + 1;
//    }
//    mySerial.write(buf);
  }
}  


=======

SoftwareSerial BTSerial(10, 11); // RX | TX


void setup() {
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more

 }

void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());

}
>>>>>>> origin/master
