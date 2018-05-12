#pragma once
#include "network/packet.h"
#include "common/common.h"

class Pod
{
private:
	GetError error;
	uint8_t state;
	SensorPacket packet;
	int sendCommand(uint8_t command)
	{
		int errcode = 0;
		CommandPacket packet(command);

		/* code for sending this packet to the pod */

		return errcode;
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
	int setReady()
	{
		return sendCommand(READY);

		//state = packet.gError.gAccSensor3()
	}
	int setAccel()
	{
		if (gState() == READY)
			return sendCommand(ACCEL);
		else return 0;
	}

	/* Don't use this function or you'll be >> rejected << */
	//int setCoast()
	//{
	//	return sendCommand(COAST);
	//}

	int setBrake()
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