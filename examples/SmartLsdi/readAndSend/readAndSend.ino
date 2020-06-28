//Programa : RFID - Controle de Acesso leitor RFID
//Autor : Lucas Alves

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>  

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
SoftwareSerial mySerial(0,1); //RX, TX 

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

char st[20];

void setup(){
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  //Define o número de colunas e linhas do LCD:
  lcd.begin(16, 2);
  mensageminicial();
  
  mySerial.begin(38400); //Inicia a serial
}

void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
  
  if (conteudo.substring(1) == "3A 9C A8 B5") //UID 1 - Cartao
  {
    Serial.println("Ola Lucas!");
    Serial.println("Por Favor, Aguarde!");
    //enviaCartao(conteudo.substring(1)); - //envia o código lido
    mySerial.print("L");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem-Vindo, Lucas!!");
    lcd.setCursor(0, 1);
    lcd.print("Acesso liberado!");
    delay(3000);
    mensageminicial();
  }

  if (conteudo.substring(1) == "3A 9C A8 B5") //UID 2 - Cartao
  {
    Serial.println("Ola Cartao!");
    Serial.println("Por Favor, Aguarde!");
    //enviaCartao(conteudo.substring(1));
    mySerial.print("D");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem-Vindo, Cartao!");
    lcd.setCursor(0, 1);
    lcd.print("Acesso Negado!");
    delay(3000);
    mensageminicial();
  }
}

//este método deve enviar o conteúdo (ou só o UID) lido do cartão via bluetooth/arduino (RX/TX)
void enviaCartao(String conteudo) {
  mySerial.print(conteudo);
  delay(3000);
}

void mensageminicial()
{
  lcd.clear();
  lcd.print(" Aproxime o seu");
  lcd.setCursor(0, 1);
  lcd.print("cartao do leitor");
}
