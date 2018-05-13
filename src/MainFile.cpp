#include "Pod.hpp"
#include "network/packet.hpp"
#include "json/ArduinoJson.h"

using namespace std;

inline float32_t getFloatdata(const Pod* pod)
{
    float32_t data = 0;
    for (int i = 0; i < 4; ++i)
    {
        data &= pod->wire->read();
        unsigned int* inta = reinterpret_cast<unsigned int*>(&data);
        *inta <<= 8;
    }
    return data;
}

inline Byte getBytedata(const Pod* pod)
{
    return pod->wire->read();
}

bool readSensorPacket(const Pod* pod, SensorPacket* packet)
{
    pod->wire->beginTransmission(POD_ADDRESS);
    pod->wire->requestFrom(POD_ADDRESS, 32);

    if(pod->wire->available() != 32)
        return false;

    packet = new SensorPacket();
    //NOTE: we can add a bunch of validation here if needed
    //First bytes are separate
    packet->sStartB(getBytedata(pod));
    packet->sErrors(getBytedata(pod));
    packet->sPodSID(getBytedata(pod));

    //Each of the floats is a 4 byte float (32 bits)
    //NOTE: Can come up with a more creative Wire.read() solution later

    packet->setTimeStamp(getFloatdata(pod));
    packet->sAccSensor1(getFloatdata(pod));
    packet->sAccSensor2(getFloatdata(pod));
    packet->sAccSensor3(getFloatdata(pod));
    packet->sTempSensor1(getFloatdata(pod));
    packet->sTempSensor2(getFloatdata(pod));
    packet->sTempSensor3(getFloatdata(pod));

    packet->sEndB(getBytedata(pod));

    pod->update(packet);
    pod->wire->endTransmission();

    return !pod->check_error().hasError();
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


    bool isOK = pod.setReady();
    while (isOK)
    {
        SensorPacket* packet;
        bool packetOK = readSensorPacket(&pod, packet);


        if (!packetOK)
        {
            /* error-checking */

            unsigned code;
            Byte errors = packet->gErrors(code);

            switch (code)
            {
            case SensorPacket::ECode::OK:
                break;
            case SensorPacket::ECode::STARTBIT:
                /* TODO handle for start bit problem */
                break;
            case SensorPacket::ECode::ENDBIT:
                /* TODO handle for end bit problem */
                break;
            case SensorPacket::ECode::OTHERBIT:
                GetError err(errors);

                /* TODO handle which sensor has a problem */

            }
        }

        delete packet;
    }

    // Dummy dump to serial for now.
    DumpToSerial(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, serial);
    /* this is how you check for error (it accepts the pointer) */
}
