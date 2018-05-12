#pragma once
#include "network/packet.h"
#include "common/common.h"

class Pod
{
private:
    bool sendCommand(uint8_t command) {
        //Error checking
        if(!(command == IDLE || command == READY || command == ACCEL || command == COAST ||
            command == BRAKE || command == STOP))
            return false;
        }

        if(command == COAST) //Not allowed to switch to COAST command
            return false;

        if(this.state == IDLE && command != READY) 
            return false;

        if(command == ACCEL && this.state != READY)
            return false;

        if(command == BRAKE && this.state != ACCEL)
            return false;

        //Can check if we need to add more error checking here

        Wire.beginTransmission(POD_ADDRESS);
        byte buffer[3];
        buffer[0] = STX;
        buffer[1] = command;
        buffer[2] = ETX;
        Wire.write(buffer,3);
        Wire.endTransmission();
        return true;
    }
public:
    Pod() : state(IDLE) {}

    inline uint8_t gState()
    {
        return state;
    }
    void update(SensorPacket &pack)
    {
        packet = pack;
    }

    /* command functions */
    bool setReady()
    {
        return sendCommand(READY);

        //state = packet.gError.gAccSensor3()
    }
    bool setAccel()
    {
        if (gState() == READY)
            return sendCommand(ACCEL);
        else return 0;
    }

    /* Don't use this function or you'll be >> rejected << */
    //bool setCoast()
    //{
    //  return sendCommand(COAST);
    //}

    bool setBrake()
    {
        if (gState() == ACCEL)
        {
            if (!getVelo())
            {
                state = STOP;
            }
            sendCommand(BRAKE);
            return 1;
        }
        else return 0;
        return sendCommand(BRAKE);
    }
    bool setStop()
    {
        return sendCommand(STOP);
    }

    /* get velocity */
    float32_t getVelo()
    {
        auto velocity = integrate(ave({ packet->gAccSensor1(), packet->gAccSensor2(), packet->gAccSensor3() }));
        float32_t velocity;
        return velocity;
    }

    /* get acceleration */
    float32_t getAccel()
    {

    }

    /* get Temperature */
    float32_t getTemp()
    {

    }

    /* get Distance */
    int getDist()
    {

    }

    GetError& check_error()
    {
        error.setError(packet);
    }
};


void somefunction()
{
    Pod pod;
    bool isOK = pod.setReady();
    if (isOK)
    {
        bool isOK = pod.setAccel();
        if (isOK)
        {

        }
    }

}
