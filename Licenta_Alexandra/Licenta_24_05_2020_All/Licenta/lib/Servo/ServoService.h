#ifndef SERVOSERVICE_H_
#define SERVOSERVICE_H_

#include <Arduino.h>
#include <Servo.h>

#define ACESS_GATE_OPEN_POS     80u
#define ACESS_GATE_CLOSE_POS    180u
#define EXIT_GATE_OPEN_POS      100u
#define EXIT_GATE_CLOSE_POS     10u

uint8_t isServoInited(void);
void servoGatesInit(void);
void servoAccessGateOpen(void);
void servoAccessGateClose(void);
void servoExitGateOpen(void);
void servoExitGateClose(void);
void servoAllGatesOpen(void);
void servoAllGatesClosed(void);
#endif