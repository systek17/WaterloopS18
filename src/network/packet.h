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
		/* Pod State ID */
		int gPodSID() //First Bit
		{
			return eStates & BIT0;
		}
		/* Acceleration Sensor 1 */
		int gAccSensor1() //Second Bit
		{
			return eStates & BIT1;
		}

		/* Acceleration Sensor 2 */
		int gAccSensor2() //Third Bit
		{
			return eStates & BIT2;
		}

		/* Acceleration Sensor 3 */
		int gAccSensor3() //Fourth Bit
		{
			return eStates & BIT3;
		}

		/* Temperature Sensor 1 */
		int gTempSensor1() //Fifth Bit
		{
			return eStates & BIT4;
		}

		/* Temperature Sensor 2 */
		int gTempSensor2() //Sixth Bit
		{
			return eStates & BIT5;
		}

		/* Temperature Sensor 3 */
		int gTempSensor3() //Seventh Bit
		{
			return eStates & BIT6;
		}
	} gError;
};

struct CommandPacket
{
	const uint_8 startByte = 0x56;
	uint_8 stateID;
	const uint_8 endByte = 0x23;
};