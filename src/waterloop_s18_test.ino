#include "Pod.hpp"
#include <Wire.h>
#include <Arduino.h>
#include "network/packet.hpp"
#include "json/ArduinoJson.hpp"

uint8_t POD_ADDRESS = 0x5A;

#define STX = 0x56;
#define ETX = 0x32;

SensorPacket sensorPacket;

bool readSensorPacket(Pod & pod) {
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


void DumpToSerial(float velocity, float distance, 
                  float acceleration, float propulsion,
                  float brakingTemp, float motherboardTemp,
                  float podState, float timeFromStart) {

    // Need to dump data to a jason file.
    StaticJsonBuffer<512> jsonBuffer;

    JsonObject & root = jsonBuffer.createObject();

    // Add values in the json object.
    root["distance"] = distance;
    root["acceleration"] = acceleration;
    root["propulsion_temp"] = propulsion;
    root["braking_temp"] = brakingTemp;
    root["motherboard_temp"] = motherboardTemp;
    root["podstate"] = podState;
    root["time_since_start"] = timeFromStart;

    // Dump the data to serial in a pretty format.
    root.prettyPrintTo(Serial);
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

    // Dummy dump to serial for now.
    DumpToSerial(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

    /* this is how you check for error (it accepts the pointer) */
    GetError error = pod.check_error(packet);
    error.gAccSensor1();
}

