//Programa : Modulo Arduino Bluetooth HC-05 - Envio
//Autor : FILIPEFLOP
//Carrega a biblioteca SoftwareSerial

#include <SoftwareSerial.h>

//Define os pinos para a serial
SoftwareSerial mySerial(5, 6); // RX, TX
String buf;

void setup(){

 //Inicializa a serial nas portas 10 e 11
  mySerial.begin(38400);
}

void loop(){
 
  buf = "60 1D A9 AB";
  mySerial.print(buf);
  //Serial.println(buf);
  delay(3000);
  
  buf = " F5 6A 08 88";
  mySerial.print(buf);
  //Serial.println(buf);
  delay(3000);

}
