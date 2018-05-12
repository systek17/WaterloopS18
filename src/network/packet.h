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

// char static_assert_float32[1 - (2 * ((sizeof(float) * CHAR_BIT) != 32))];

struct SensorPacket
{
	uint8_t startByte;
	uint8_t eStates;
	uint8_t currentPodState;
	float tstamp;
	float accdata1;
	float accdata2;
	float accdata3;
	float tempdata2;
	float tempdata3;
	float tempdata4;
	uint8_t endByte;

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
};

struct CommandPacket
{
	const uint8_t startByte = 0x56;
	uint8_t stateID;
	const uint8_t endByte = 0x23;
	CommandPacket(const uint8_t &command) : stateID(command) {}
};

class Pod
{
private:

	int sendCommand(uint8_t command)
	{
		int errcode = 0;
		CommandPacket packet(command);

		/* code for sending this packet to the pod */

		return errcode;
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
	int setCoast()
	{
		return sendCommand(COAST);
	}
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
};