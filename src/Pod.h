#pragma once
#include "network\packet.h"

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

	/* command functions */
	bool setReady()
	{
		return sendCommand(READY);

		//state = packet.gError.gAccSensor3()
	}
	bool setAccel()
	{
		return sendCommand(ACCEL);
	}

	/* Don't use this function or you'll be >> rejected << */
	//bool setCoast()
	//{
	//	return sendCommand(COAST);
	//}

	bool setBrake()
	{
		return sendCommand(BRAKE);
	}
	bool setStop()
	{
		return sendCommand(STOP);
	}

	/* get velocity */
	int getVelo(SensorPacket * packet)
	{

	}

	/* get acceleration */
	float getAccel(SensorPacket * packet)
	{

	}

	/* get Temperature */
	float getTemp(SensorPacket * packet)
	{

	}

	/* get Distance */
	int getDist(SensorPacket * packet)
	{

	}

	GetError& check_error(SensorPacket * packet)
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
