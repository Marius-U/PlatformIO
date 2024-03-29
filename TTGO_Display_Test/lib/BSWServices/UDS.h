#ifndef UDS_HEADER
#define UDS_HEADER

#include <Arduino.h>
#include <string.h>
#include <CAN.h>

/*************MacroDefinitions***********/

#define MAX_DLC 0x08u
#define PCI     0x00u
#define SID     0x01u

#define UDS_REQUEST_ID      0x100u
#define UDS_RESPONSE_ID     0x101u

//Diagnostic and Communication Management Functional Unit 
#define DIAGNOSTIC_SESION_CONTROL   0x10u
#define ECU_RESET                   0x11u
#define READ_DID                    0x22u
#define SECURRITY_ACCESS            0x27u
#define WRITE_DID                   0x2Eu
#define ROUTINE_CONTROL             0x31u
#define REQUEST_DOWNALOAD           0x34u
#define TRANSFER_DATA               0x36u
#define REQUEST_TRANSFER_EXIT       0x37u

//Sub-Function ID (SBF)
#define DEFAULT_SESSION             0x01u
#define PROGRAMMING_SESSION         0x02u
#define EXTENDED_DIAG_SESSION       0x03u
#define READ_FINGERPRINT            0xF15Bu
#define WRITE_FINGERPRINT           0xF15Au

#define HARD_RESET                  0x01u

//Negative Response code (NRC)
#define SERVICE_NOT_SUPPORTED   0x11u
#define CONDITIONS_NOT_CORRECT  0x22u
#define REQUEST_OUT_OF_RANGE    0x31u
#define SECURITY_ACCESS_DENIED  0x33u

/***************************************/
/*************GlobalVariables***********/

/***************************************/
/*************GlobalFunctions***********/

void UDS_main(void);
int8_t UDS_process(void);
int8_t UDS_getActiveSession(void);
int8_t UDS_setRxBuffer(uint8_t buffer[]);

/***************************************/

#endif