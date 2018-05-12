#pragma once
#include "network\packet.h"
#include <Wire.h>

uint8_t POD_ADDRESS = 0x5A;

#define STX = 0x56;
#define ETX = 0x32;


void setup() {
	Wire.begin();
	Serial.begin(9600);
}

void loop() {

}



int main()
{

}