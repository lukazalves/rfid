#include <DHT.h>
#include <SoftwareSerial.h>
#include "ServerAC.h"

#define DHTTYPE           DHT11
#define NUM_SENSORS       4
#define NUM_ACTUATORS     1

const int DELAY_TIME      = 3000;    /* Time to wait to take the next measurements */
const int dhtPin          = A0;     /* DHT11 pin (Humidity and Temperature sensor) */
const int gasDigitalPin   = 4;      /* Digital gas sensor pin */
const int gasAnalogPin    = A1;     /* Analog gas sensor pin */
const int softwareRX      = 7;      /* pin used as serial reciever */
const int softwareTX      = 8;      /* pin used as serial transmissor */

float SENSOR_VALUES[NUM_SENSORS];   /* All the measurements will be stored in this array */
float ACTUATOR_VALUES[NUM_ACTUATORS]; /* When writing a command to a actuator, the value will be stored here */

DHT dhtSensor(dhtPin, DHTTYPE); /*The DHT11 sensor */
SoftwareSerial BTSerial(softwareRX, softwareTX); /* The bluetooth module */
IRsend irsend; /* library to control infrared leds */


void setup() {
  pinMode(13, OUTPUT);
  BTSerial.begin(9600);
  Serial.begin(9600);
  dhtSensor.begin();
}

void loop() {
  /* Read and register the values from the gas sensor */
  registerMeasurement(readAnalogGas(gasAnalogPin));
  registerMeasurement(readDigitalGas(gasDigitalPin));
  /* Read and register the thumidity and temperature from the DHT11 sensor */
  registerMeasurement(dhtSensor.readHumidity());
  registerMeasurement(dhtSensor.readTemperature());

  /* Send those values to the serial port, and therefore, the bluetooth module */
  sendMeasurements();

  /* if receive commands from bluetooth, interpret it as the wanted temperature in celsius */
  if (readCommands()) {
    int khz = 38;
    int temperature = ACTUATOR_VALUES[0];
    byte temperatureBuff[MESSAGE_SIZE]; /* MESSAGE_SIZE is defined in ServerAC.h */
    
    getTemperatureRepresentation(temperatureBuff, MESSAGE_SIZE, temperature);
    sendRawByBit(irsend, temperatureBuff, khz);
  }

  delay(DELAY_TIME);
}

float readDigitalGas(int pin) {
  return (float)digitalRead(pin);
}

float readAnalogGas(int pin) {
  return (float)analogRead(pin);
}

/*
 * Put the value of 'measurement' in the SENSOR_VALUES array
 */
void registerMeasurement(float measurement) {
  static int count_measures = 0;
  SENSOR_VALUES[count_measures++] = measurement;
  count_measures %= NUM_SENSORS;
}

/*
 * Send all the measurements as a string through Bluetooth and Serial
 * communication, in the format "H;analogGas;digitalGas;humidity;temperature;F;"
 * 
 * The string is also sent via Serial, so it can be read by the raspberry through USB
 */
void sendMeasurements() {
  /* Bluetooth section */
  BTSerial.print("H");
  for (int i = 0; i < NUM_SENSORS; i++) {
    BTSerial.print(";");
    BTSerial.print(SENSOR_VALUES[i]);
  }
  BTSerial.println(";F;");

  
  /* Serial (USB) section */
  Serial.print("H");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(";");
    Serial.print(SENSOR_VALUES[i]);
  }
  Serial.println(";F;");
}


/*
 * Read commands in the form "H;temperature;F" and place the value in ACTUATOR_VALUES array
 * returns true if the command is valid, false otherwise
 */
bool readCommands() {
  enum states {START, FIRST_SEMICOLON, FIRST_NUMBER, REMAINING_NUMBERS, SECOND_SEMICOLON, END} state;

  String acTemperature = String("");
  state = START;
  while (BTSerial.available() && state != END) {
    
    char c = BTSerial.read();
    switch (state) {
      case START:
        if (c == 'H')
          state = FIRST_SEMICOLON;
        break;
      case FIRST_SEMICOLON:
        if (c == ';')
          state = FIRST_NUMBER;
        else
          state = START;
        break;
      case FIRST_NUMBER:
        if (isDigit(c)) {
          acTemperature.concat(c);
          state = REMAINING_NUMBERS;
        } else {
          state = START;
        }
        break;
      case REMAINING_NUMBERS:
        if (isDigit(c))
          acTemperature.concat(c);
        else if (c == ';')
          state = SECOND_SEMICOLON;
        else
          state = START;
        break;
      case SECOND_SEMICOLON:
        if (c == 'F')
          state = END;
        else
          state = START;
        break;
      case END:
        break;
    }
  }

  if (state == END)
    ACTUATOR_VALUES[0] = acTemperature.toInt();

  return state == END;
  
}
