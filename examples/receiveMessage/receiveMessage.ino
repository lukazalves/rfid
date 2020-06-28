//Programa : Receber Mensagem via Bluetooth e Escrever no Monitor Serial
//Autor : Lucas Alves
#include <SoftwareSerial.h>

String buf;

void setup(){
  
  SoftwareSerial mySerial(10, 11); // RX, TX
  Serial.begin(9600);

}
void loop(){
  
  buf = "";
  
  while(Serial.available() > 0){
    buf = Serial.read();
    Serial.println(buf);
   }

}
