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
public:

	/* command functions */
	int setReady()
	{
		return sendCommand(READY);

		//state = packet.gError.gAccSensor3()
	}
	int setAccel()
	{
		return sendCommand(ACCEL);
	}

	/* Don't use this function or you'll be >> rejected << */
	//int setCoast()
	//{
	//	return sendCommand(COAST);
	//}

	int setBrake()
	{
		return sendCommand(BRAKE);
	}
	int setStop()
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
