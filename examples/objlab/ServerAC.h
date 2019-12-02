#ifndef SERVERAC_H
#define SERVERAC_H

#include <Arduino.h>
#include <IRremote.h>


#define HEADER_MARK     2900
#define HEADER_SPACE    1650
#define SEPARATOR_MARK  400
#define MESSAGE_BITS    112
#define SET_BIT_TIME    400
#define CLEAR_BIT_TIME  1150
#define MIN_TEMP        16
#define MAX_TEMP        25
#define BYTE07_MIN      B11110000
#define BYTE13_MIN      B10110010

#define MESSAGE_SIZE  (MESSAGE_BITS)/8 + !!((MESSAGE_BITS)%8)


int getBit(byte bitArr[], unsigned int bitpos);
void getTemperatureRepresentation(byte out[], int len, int temperature);
void sendRawByBit(IRsend irsend, byte buff[], int khz);

#endif
