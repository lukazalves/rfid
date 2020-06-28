//Programa : Modulo Arduino Bluetooth HC-05 - Envio
//Autor : FILIPEFLOP
//Carrega a biblioteca SoftwareSerial

#include <SoftwareSerial.h>

//Define os pinos para a serial
SoftwareSerial mySerial(10, 11); // RX, TX
String buf;

void setup(){

 //Inicializa a serial nas portas 10 e 11
  mySerial.begin(38400);
}

void loop(){
  
  //Envia pela serial o caracter L
  buf = "teste";
  mySerial.print(buf);
  Serial.println(buf);
  delay(3000);
  
  //Envia pela serial o caracter D
  buf = "ok";
  mySerial.print(buf);
  Serial.println(buf);
  delay(3000);

}
