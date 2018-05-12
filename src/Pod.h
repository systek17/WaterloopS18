#pragma once
#include "network/packet.h"
#include "common/common.h"
#include <Wire.h>


#define POD_ADDRESS 0x5A;

class Pod
{
private:

	Wire *wire;
	SensorPacket *packet;

	GetError error;
	uint8_t state;
	bool sendCommand(uint8_t command)
	{
		int errcode = 0;
		CommandPacket packet(command);

		//Error checking
		if(!(command == IDLE || command == READY || command == ACCEL || command == COAST ||
			command == BRAKE || command == STOP))
			return false;


		if(command == COAST) //Not allowed to switch to COAST command
			return false;

		if(this->state == IDLE && command != READY)
			return false;

		if(command == ACCEL && this->state != READY)
			return false;

		if(command == BRAKE && this->state != ACCEL)
			return false;


		//Can check if we need to add more error checking here

		wire->beginTransmission(POD_ADDRESS);
		uint8_t buffer[3];
		buffer[0] = STX;
		buffer[1] = command;
		buffer[2] = ETX;
		wire->write(buffer,3);
		wire->endTransmission();
		return true;
	}
public:
	Pod(Wire* w) : state(IDLE), wire(w) {}

	inline uint8_t gState()
	{
		return state;
	}
	void update(SensorPacket& pack)
	{
		packet = &pack;
	}

	/* command functions */
	bool setReady()
	{
		return sendCommand(READY);
	}
	bool setAccel()
	{
		if (gState() == READY)
			return sendCommand(ACCEL);
		else return 0;
	}

	bool setBrake()
	{
		if (gState() == ACCEL)
		{
			if (getVelo() == float32_t(0))
			{
				state = STOP;
			}
			sendCommand(BRAKE);
			return true;
		}
		else return false;
	}

	/* get velocity */
	float32_t getVelo()
	{
		auto velocity = integrate(ave(vector<float32_t>{ packet->gAccSensor1(), packet->gAccSensor2(), packet->gAccSensor3() }));
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
