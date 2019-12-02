// Programa: Sensor DHT11 - Envio de dados via Bluetooth
// Autor: FILIPEFLOP
 
 
 
 
 
void setup()
{
  Serial.begin(9600);
  // Aguarda 1 seg antes de acessar as informações do sensor
  delay(1000);
}
 
void loop()
{
  float h = 10;
  float t = 10;
 
  // Mostra os valores lidos, na serial
  Serial.print("Temp. = ");
  Serial.print(t);
  Serial.print(" C ");
  Serial.print("Um. = ");
  Serial.print(h);
  Serial.println(" % ");
 
  // Nao diminuir muito o valor abaixo
  // O ideal e a leitura a cada 2 segundos
  delay(2000);
}
