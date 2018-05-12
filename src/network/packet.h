


#define IDLE 0x00
#define READY 0x01
#define ACCEL 0x02
#define COAST 0x03
#define BRAKE 0x04
#define STOP 0x05

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
};

struct CommandPacket
{
	uint_8 startByte;
	uint_8 stateID;
	uint_8 endByte;
};

