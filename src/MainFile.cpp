<<<<<<< HEAD
#include "Pod.hpp"
#include <Wire.h>
#include <Arduino.h>
#include "network/packet.hpp"
#include "json/ArduinoJson.hpp"
||||||| merged common ancestors
#include "Pod.h"
#include <Wire.h>
#include "network/packet.h"
#include "json/ArduinoJson.h"
=======
#include "Pod.h"
#include "network/packet.h"
#include "json/ArduinoJson.h"
>>>>>>> 1e91f9e55578762c0210d0c79f5338bd2162ad0c

using namespace std;




bool readSensorPacket(Pod* pod)
{
  pod->wire->beginTransmission(POD_ADDRESS);
  pod->wire->requestFrom(POD_ADDRESS, 32);

  if(pod->wire->available() != 32)
    return false;
  SensorPacket sensorPacket;
  //NOTE: we can add a bunch of validation here if needed
  //First bytes are separate
  sensorPacket.startByte = pod->wire->read();
  sensorPacket.eStates = pod->wire->read();
  sensorPacket.currentPodStateID = pod->wire->read();

  //Each of the floats is a 4 byte float (32 bits)
  //NOTE: Can come up with a more creative Wire.read() solution later
  for(int i=0; i<4; i++)
    sensorPacket.tstamp.arr[i] = pod->wire->read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata1.arr[i] = pod->wire->read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata2.arr[i] = pod->wire->read();

  for(int i=0; i<4; i++)
    sensorPacket.accdata3.arr[i] = pod->wire->read();

  for (int i = 0; i < 4; i++)
<<<<<<< HEAD
      sensorPacket.tempdata1.arr[i] = Wire.read();
||||||| merged common ancestors
	  sensorPacket.tempdata1.arr[i] = Wire.read();
=======
	  sensorPacket.tempdata1.arr[i] = pod->wire->read();
>>>>>>> 1e91f9e55578762c0210d0c79f5338bd2162ad0c

  for(int i=0; i<4; i++)
    sensorPacket.tempdata2.arr[i] = pod->wire->read();

  for(int i=0; i<4; i++)
    sensorPacket.tempdata3.arr[i] = pod->wire->read();

  sensorPacket.endByte = pod->wire->read();

  pod->update(sensorPacket);
  pod->wire->endTransmission();

	//GetError error = pod.check_error(packet);
  return true;
}


void DumpToSerial(float velocity, float distance,
                  float acceleration, float propulsion,
                  float brakingTemp, float motherboardTemp,
                  float podState, float timeFromStart, Serial serial) {

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
    root.prettyPrintTo(serial);
}

void setup(Pod *pod, Serial* serial)
{
	pod->wire->begin();
	serial->begin(9600);
}

int main()
{
<<<<<<< HEAD
    Pod pod;

    bool isOK;
    while (isOK)
    {
        isOK = readSensorPacket(pod);
    }
||||||| merged common ancestors
	Pod pod;
<<<<<<< HEAD
	bool isOK;
	while (isOK)
	{
		isOK = readSensorPacket(pod);
	}
=======
=======
	Wire wire;
	Pod pod(wire);

	Serial serial;
	setup(&pod, &serial);

	bool isOK;
	while (isOK)
	{
		isOK = readSensorPacket(pod);
	}
>>>>>>> 1e91f9e55578762c0210d0c79f5338bd2162ad0c


<<<<<<< HEAD
    /* this is how you check for error (it accepts the pointer) */
    GetError error = pod.check_error(packet);
    error.gAccSensor1();
||||||| merged common ancestors
>>>>>>> edd3fd63b2663315c244fc9bdbd242e7e61e4a33
	/* this is how you check for error (it accepts the pointer) */
	GetError error = pod.check_error(packet);
	error.gAccSensor1();
=======
    // Dummy dump to serial for now.
    DumpToSerial(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, serial);
	/* this is how you check for error (it accepts the pointer) */
>>>>>>> 1e91f9e55578762c0210d0c79f5338bd2162ad0c
}
