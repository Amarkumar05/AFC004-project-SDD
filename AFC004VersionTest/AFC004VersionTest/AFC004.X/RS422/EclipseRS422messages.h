/*
 * Filename: EclipseRS422messages.h
 * 
 * Author: Henry Gilbert
 * 
 * Date: 8 April 2022 
 * 
 * Description: File used to define function prototypes, device number and 
 *              command number enumerations, and relevant structures for 
 *              processing Eclipse's RS422 message structure. 
 *  
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */


#ifndef ECLIPSE_RS422_MESSAGES_H
#define ECLIPSE_RS422_MESSAGES_H


/**************  Included File(s) **************************/
#include <stdint.h>
#include "CircularBuffer.h"
#include "ARINC_typedefs.h"


/**************  Macro Definition(s) ***********************/
#define ECLIPSE_RS422_ADC_COMPUTED_DATA_MSG_LENGTH  0x51 // Expected length field value for ADC computed data command
#define ECLIPSE_RS422_ADC_STATUS_MSG_LENGTH         0x05 // Expected length field value for ADC status command
#define ECLIPSE_RS422_AHRS_CURRENT_DATA_MSG_LENGTH 0x15 /* Messages lengths to transmit. Length includes header, crc, etc. */

/**************  Type Definition(s) ************************/
/* Device codes for Eclipse's RS422 systems */
typedef enum EclipseRS422deviceNumber_t {
    LEFT_AHRS = 0x81,
    RIGHT_AHRS = 0x82,
    LEFT_ADC = 0x85,
    RIGHT_ADC = 0x86,
    LEFT_PFD = 0x51,
    RIGHT_PFD = 0x52,
} EclipseRS422deviceNumber;

/* RS422 message commands for Eclipse's RS422 specification */
typedef enum EclipseRS422cmd_t {
    GROUND_MAINTENANCE = 0x02,
    ADC_COMPUTED_DATA_CMD = 0x30,
    ADC_STATUS_CMD = 0x31,
    AHRS_CURRENT_DATA_CMD = 0x32,
    SOFTWARE_VERSION_CMD = 0xF8,
    HARDWARE_SERIAL_NUMBER_CMD = 0xFA
} EclipseRS422cmd;

/* Eclipse message config structure */
typedef struct {
    EclipseRS422cmd cmd;
    EclipseRS422deviceNumber leftSource;
    EclipseRS422deviceNumber rightSource;
    EclipseRS422deviceNumber leftDestination;
    EclipseRS422deviceNumber rightDestination;
    uint8_t length; // Length of cmd fields + data field (bytes).
} EclipseRS422msgConfig;

/* Eclipse message structure */
typedef struct {
    const EclipseRS422msgConfig* msgConfig;
    uint8_t* data; /* Can be configured to transmit or receive */
    uint32_t timeStamp_counts; // Counts in 10ms increments. 
    const uint32_t timeStamp_max_counts; // max timeout stamps that can occur before bus failure;
    bool hasBusFailed; // important- this must be initialized to true on startup. 
} EclipseRS422msg;


/**************  Function Prototype(s) *********************/
/* Parse the UART2 receive circular buffer for new Eclipse Aviation RS422 messages */
bool EclipseRS422_ProcessNewMessage(circBuffer_t * const rxCircBuffer, // circular buffer object
        const uint8_t rxMsgsSize, // Number of received messages in array
        EclipseRS422msg * const rxMsgs, // received messages array
        size_t * const returnMsgIndex); // return parameter for a message index if a valid msg was found. 

/* Construct an RS422 transmit message and flush to the transmit circular buffer */
void EclipseRS422_ConstructTxMsg(EclipseRS422msg * const rs422TxMsg, /* Pointer to RS422 Eclipse message */
        circBuffer_t * const txBuff, /* Circular buffer destination to flush resultant array */
        uint32_t * const arincArray, /* Array of ARINC words to send */
        const size_t numArincWords, /* Number of ARINC words to send in the message */
        const uint8_t magHeadingSDI, /* SDI of magnetic heading to set L/R. Mag heading is arbitrary */
        const size_t numBytesToFlush); /* Number of bytes to flush is the size of the desired tx message in bytes */

void EclipseRS422_CreateARINCWords(const EclipseRS422msg * const RS422Msg, /* Pointer to Eclipse rx msg array */
        ARINC429_RxMsgArray * const ArincMsgArray, /* Pointer to ARINC msg array */
        const size_t msgIdx, /* Number of ARINC words to process */
        const size_t numMsgsInRS422Array); /* Total number of members in input EclipseRS422msg array */

bool EclipseRS422_processBusFailure(EclipseRS422msg * const RS422Msg,
        const size_t numMsgs);

#endif /* ECLIPSE_RS422_MESSAGES_H */