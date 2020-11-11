//Programa : RFID - Controle de Acesso leitor RFID
//Autor : Lucas Alves

#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>  

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
SoftwareSerial mySerial(5, 6); //RX, TX
String buf; 

void setup(){
  
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  mySerial.begin(38400); //Inicia a serial
}

void loop(){
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }
  
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++){
    
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  
  }
  
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
  
  if (conteudo.substring(1) == "60 1F 0D C5"){ //UID 1 - Cartao
      Serial.println("Ola Lucas!");
      Serial.println("Por Favor, Aguarde!");
      enviaCartao(conteudo.substring(1));
      
  }

  if (conteudo.substring(1) == "60 1D A9 AB"){ //UID 2 - Cartao
      Serial.println("Ola Cartao!");
      Serial.println("Por Favor, Aguarde!");
      enviaCartao(conteudo.substring(1));
  }

  if (conteudo.substring(1) == "F5 6A 08 88"){ //UID - CHAVEIRO
      Serial.println("Ola Chaveiro!");
      Serial.println("Por Favor, Aguarde!");
      enviaCartao(conteudo.substring(1));
  }
  
}

//este método deve enviar o conteúdo (ou só o UID) lido do cartão via bluetooth/arduino (RX/TX)
void enviaCartao(String teste) {
  mySerial.print(teste);
  delay(3000);
} 
