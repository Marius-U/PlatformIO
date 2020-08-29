#include <ServoService.h>

/***************Local variables********************/
/**************************************************/
static uint8_t servoIsServoInited;
/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/

Servo servo_Access;  // create servo object to control a servo motor
Servo servo_Exit;    // create servo object to control a servo motor

uint8_t isServoInited(void)
{
    return servoIsServoInited;
}

void servoGatesInit(void)
{
    if(!servoIsServoInited)
    {
        servo_Access.attach(5);
        servo_Exit.attach(6);
        servo_Exit.write(EXIT_GATE_CLOSE_POS);
        servo_Access.write(ACESS_GATE_CLOSE_POS);
        servoIsServoInited = 0x01u;
    }
}

void servoAccessGateOpen(void)
{
    servo_Access.write(ACESS_GATE_OPEN_POS);
}
void servoAccessGateClose(void)
{
    servo_Access.write(ACESS_GATE_CLOSE_POS);
}
void servoExitGateOpen(void)
{
    servo_Exit.write(EXIT_GATE_OPEN_POS);
}
void servoExitGateClose(void)
{
    servo_Exit.write(EXIT_GATE_CLOSE_POS);
}
void servoAllGatesOpen(void)
{
    servo_Access.write(ACESS_GATE_OPEN_POS);
    servo_Exit.write(EXIT_GATE_OPEN_POS);
}
void servoAllGatesClosed(void)
{
    servo_Access.write(ACESS_GATE_CLOSE_POS);
    servo_Exit.write(EXIT_GATE_CLOSE_POS);
}