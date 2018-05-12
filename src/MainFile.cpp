#include "Pod.hpp"
#include "network/packet.hpp"
#include "json/ArduinoJson.h"

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
        sensorPacket.tempdata1.arr[i] = pod->wire->read();

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
    Wire wire;
    Pod pod(wire);

    Serial serial;
    setup(&pod, &serial);

    bool isOK;
    while (isOK)
    {
        isOK = readSensorPacket(pod);
    }

    // Dummy dump to serial for now.
    DumpToSerial(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, serial);
    /* this is how you check for error (it accepts the pointer) */
}
