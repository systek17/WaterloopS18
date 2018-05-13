#pragma once
#include <cstdint>
#include "../common/common.hpp"

#define IDLE 0x00
#define READY 0x01
#define ACCEL 0x02
#define COAST 0x03
#define BRAKE 0x04
#define STOP 0x05

#define STX 0x56
#define ETX 0x32

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

class SensorPacket
{
private:
    Byte startByte;
    Byte eStates;
    Byte currentPodStateID;
    float32_t tstamp;
    float32_t accdata1;
    float32_t accdata2;
    float32_t accdata3;
    float32_t tempdata1;
    float32_t tempdata2;
    float32_t tempdata3;
    float32_t endByte;

public:
    SensorPacket() {};
    enum ECode
    {
        OK = 0,
        STARTBIT,
        ENDBIT,
        OTHERBIT
    };

    /* get the state of all errors */
    Byte gErrors(unsigned& error_code)
    {
        if (startByte != STX)
            error_code = STARTBIT;
        else if (endByte != ETX)
            error_code = ENDBIT;
        else if (eStates)
            error_code = OTHERBIT;
        else
            error_code = OK;

        return eStates;
    }

    Byte gErrors() const
    {
        return eStates;
    }

    /* set the state of all erorrs */
    void sErrors(const Byte& data)
    {
        eStates = data;
    }

    /* set the start byte */
    void sStartB(const Byte& data)
    {
        startByte = data;
    }

    /* set the end byte */
    void sEndB(const Byte& data)
    {
        endByte = data;
    }

    /* Time Stamp */
    float32_t getTimeStamp() const
    {
        return tstamp;
    }
    void setTimeStamp(const float32_t& stamp)
    {
        tstamp = stamp;
    }

    /* Pod State ID */
    Byte gPodSID() const //First Bit
    {
        return currentPodStateID;
    }
    void sPodSID(const Byte& ID)
    {
        currentPodStateID = ID;
    }

    /* Acceleration Sensor 1 */
    float32_t gAccSensor1() const //Second Bit
    {
        return accdata1;
    }
    void sAccSensor1(const float32_t& data)
    {
        accdata1 = data;
    }

    /* Acceleration Sensor 2 */
    float32_t gAccSensor2() const //Third Bit
    {
        return accdata2;
    }
    void sAccSensor2(const float32_t& data)
    {
        accdata2 = data;
    }

    /* Acceleration Sensor 3 */
    float32_t gAccSensor3() const //Fourth Bit
    {
        return accdata3;
    }
    void sAccSensor3(const float32_t& data)
    {
        accdata3 = data;
    }

    /* Temperature Sensor 1 */
    float32_t gTempSensor1() const //Fifth Bit
    {
        return tempdata1;
    }
    void sTempSensor1(const float32_t& data)
    {
        tempdata1 = data;
    }

    /* Temperature Sensor 2 */
    float32_t gTempSensor2() const //Sixth Bit
    {
        return tempdata2;
    }
    void sTempSensor2(const float32_t& data)
    {
        tempdata2 = data;
    }

    /* Temperature Sensor 3 */
    float32_t gTempSensor3() const //Seventh Bit
    {
        return tempdata3;
    }
    void sTempSensor3(const float32_t& data)
    {
        tempdata3 = data;
    }
};

struct GetError
{
    Byte error_state;
    GetError(const Byte& err) : error_state(err) {}

    /* Pod State ID */
    int gPodSID() const //First Bit
    {
        return error_state & BIT0;
    }
    /* Acceleration Sensor 1 */
    int gAccSensor1() const //Second Bit
    {
        return error_state & BIT1;
    }

    /* Acceleration Sensor 2 */
    int gAccSensor2() const //Third Bit
    {
        return error_state & BIT2;
    }

    /* Acceleration Sensor 3 */
    int gAccSensor3() const //Fourth Bit
    {
        return error_state & BIT3;
    }

    /* Temperature Sensor 1 */
    int gTempSensor1() const //Fifth Bit
    {
        return error_state & BIT4;
    }

    /* Temperature Sensor 2 */
    int gTempSensor2() const //Sixth Bit
    {
        return error_state & BIT5;
    }

    /* Temperature Sensor 3 */
    int gTempSensor3() const //Seventh Bit
    {
        return error_state & BIT6;
    }

    /* check if there is error at all */
    bool hasError() const
    {
        return error_state > 0;
    }
};

struct CommandPacket
{
    const Byte startByte = STX;
    Byte stateID;
    const Byte endByte = ETX;
    CommandPacket(const Byte &command) : stateID(command) {}
};
