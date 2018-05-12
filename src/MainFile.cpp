#pragma once
#include "Pod.h"
#include <Wire.h>

uint8_t POD_ADDRESS = 0x5A;

#define STX = 0x56;
#define ETX = 0x32;
SensorPacket sensorPacket;

bool readSensorPacket(Pod& pod) {
  Wire.beginTransmission(POD_ADDRESS);
  Wire.requestFrom(POD_ADDRESS, 32);

  if(Wire.available() != 32)
    return false;

  //NOTE: we can add a bunch of validation here if needed
  //First bytes are separate
  sensorPacket.startByte = Wire.read();
  sensorPacket.eStates = Wire.read();
  sensorPacket.currentPodStateID = Wire.read();

  //Each of the floats is a 4 byte float (32 bits)
  //NOTE: Can come up with a more creative Wire.read() solution later
  for(int i=0; i<4; i++)
    sensorPacket.tstamp.arr[i] = Wire.read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata1.arr[i] = Wire.read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata2.arr[i] = Wire.read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata3.arr[i] = Wire.read();

  for (int i = 0; i < 4; i++)
	  sensorPacket.tempdata1.arr[i] = Wire.read();

  for(int i=0; i<4; i++)
    sensorPacket.tempdata2.arr[i] = Wire.read();

  for(int i=0; i<4; i++)
    sensorPacket.tempdata3.arr[i] = Wire.read();

  sensorPacket.endByte = Wire.read();
  pod.update(sensorPacket);

  Wire.endTransmission();
  return true;
}


void setup() {
	Wire.begin();
	Serial.begin(9600);
}

void loop() {

}



int main()
{
	Pod pod;
	bool isOK;
	while (isOK)
	{
		isOK = readSensorPacket(pod);
	}
	/* this is how you check for error (it accepts the pointer) */
	GetError error = pod.check_error(packet);
	error.gAccSensor1();
}
