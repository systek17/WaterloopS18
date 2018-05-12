#include <string.h>
#include <Wire.h>

#include "network/packet.h"
#include "json/ArduinoJson.h"

using namespace std;

uint8_t POD_ADDRESS = 0x5A;

#define STX = 0x56;
#define ETX = 0x32;


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

int main() {

    // Dummy dump to serial for now.
    DumpToSerial(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
}
