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

struct float32_t
{
	uint8_t arr[4];
	float32_t(uint8_t input[4])
	{
		arr[0] = input[0];
		arr[1] = input[1];
		arr[2] = input[2];
		arr[3] = input[3];
	}
	void operator=(const float32_t& input)
	{
		arr[0] = input.arr[0];
		arr[1] = input.arr[1];
		arr[2] = input.arr[2];
		arr[3] = input.arr[3];
	}
};

struct SensorPacket
{
	uint8_t startByte;
	uint8_t eStates;
	uint8_t currentPodStateID;
	float32_t tstamp;
	float32_t accdata1;
	float32_t accdata2;
	float32_t accdata3;
	float32_t tempdata1;
	float32_t tempdata2;
	float32_t tempdata3;
	float32_t endByte;

	/* Time Stamp */
	float32_t getTimeStamp()
	{
		return tstamp;
	}
	void setTimeStamp(const float32_t& stamp)
	{
		tstamp = stamp;
	}

	/* Pod State ID */
	uint8_t gPodSID() const //First Bit
	{
		return currentPodStateID & BIT0;
	}
	void sPodSID(const uint8_t& ID)
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
	uint8_t error_state;
	GetError(SensorPacket* packet) : error_state(packet->eStates) {}

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

	int check_error(SensorPacket * packet)
	{
		GetError error(packet);
		//error.gPodSID();
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