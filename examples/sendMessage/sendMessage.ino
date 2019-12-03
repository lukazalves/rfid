//Programa : Modulo Arduino Bluetooth HC-05 - Envio
//Autor : FILIPEFLOP
 
//Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>  
 
//Define os pinos para a serial   
SoftwareSerial mySerial(10, 11); // RX, TX 
 
void setup()
{
  //Inicializa a serial nas portas 10 e 11
  mySerial.begin(38400);
}
 
void loop()
{
  //Envia pela serial o caracter L
  mySerial.print("L");
  delay(3000);
  //Envia pela serial o caracter D
  mySerial.print("D");
  delay(3000);
}
