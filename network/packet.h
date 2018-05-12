#include <cstdint>

#define IDLE 0x00
#define READY 0x01
#define ACCEL 0x02
#define COAST 0x03
#define BRAKE 0x04
#define STOP 0x05

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80


struct SensorPacket
{
	uint_8 startByte;
	uint_8 eStates;
	uint_8 currentPodState;
	float_32 tstamp;
	float_32 accdata1;
	float_32 accdata2;
	float_32 accdata3;
	float_32 tempdata2;
	float_32 tempdata3;
	float_32 tempdata4;
	uint_8 endByte;

	struct Error
	{
		int gPodSID()
		{
			return eStates & BIT0;
		}
		int gAccSensor1()
		{
			return eStates & BIT1;
		}
		int gAccSensor2()
		{
			return eStates & BIT2;
		}
		int gAccSensor3()
		{
			return eStates & BIT3;
		}
		int gTempSensor1()
		{
			return eStates & BIT4;
		}
		int gTempSensor2()
		{
			return eStates & BIT5;
		}
		int gTempSensor3()
		{
			return eStates & BIT6;
		}
	};
};

struct CommandPacket
{
	uint_8 startByte;
	uint_8 stateID;
	uint_8 endByte;
};



void getdata()
{
	SensorPacket sensorpak;
	sensorpak.eStates & podsID;
}