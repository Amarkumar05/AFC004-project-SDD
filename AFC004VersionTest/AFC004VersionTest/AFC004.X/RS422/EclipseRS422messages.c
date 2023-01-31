/*
 * Filename: EclipseRS422messages.c
 * 
 * Author: Henry Gilbert
 * 
 * Date: 8 April 2022 
 * 
 * Description: Module used to process Eclipse's RS422 messages format. 
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */


/**************  Included File(s) **************************/
#include "EclipseRS422messages.h"
#include <stdlib.h>
#include "ARINC.h"  
#include "CRC16bit.h"


/**************  Macro Definition(s) ***********************/
#define ECLIPSE_RS422_MESSAGE_PREAMBLE                         0xEA
#define ECLIPSE_RS422_MESSAGE_PREAMBLE_INDEX                   0   
#define ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX                1
#define ECLIPSE_RS422_MESSAGE_SOURCE_INDEX                     2
#define ECLIPSE_RS422_MESSAGE_LENGTH_INDEX                     3
#define ECLIPSE_RS422_MESSAGE_CMD_INDEX                        4
#define ECLIPSE_RS422_MESSAGE_DATA_START_OFFSET                5
#define ECLIPSE_RS422_MESSAGE_MIN_TOTAL_LENGTH                 5
#define ECLIPSE_RS422_MESSAGE_LENGTH_HEADER_AND_CRC            6
#define ECLIPSE_RS422_CRC_SEED_VALUE                           0xFFFF

/* Misc definitions */
#define NUM_BITS_IN_BYTE 8u
#define SIZE_OF_TX_CIRCBUFF_BYTES 100
#define MAX_NUM_ARINC_WORDS_CONSTRUCT_MSG  (SIZE_OF_TX_CIRCBUFF_BYTES - ECLIPSE_RS422_MESSAGE_LENGTH_HEADER_AND_CRC)/4
#define NUM_BITS_IN_UINT32 32

/* ARINC location definitions */
#define ARINC_BYTE_ONE_OFFSET 8u
#define ARINC_BYTE_TWO_OFFSET 16u
#define ARINC_BYTE_THREE_OFFSET 24u
#define NUM_BYTES_ARINC_MSG 4u
#define LS_BYTE_BITMASK 0xFFu
#define ARINC_PARITY_SET 0x80000000u
#define MAX_NUM_ARINC_MESSAGES 20u

#ifndef min 
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif 


/**************  Function Definition(s) ********************/

/* 
 * Function: EclipseRS422messages_ProcessNew
 * 
 * Description: Searches the length of a receive circular buffer for a matching 
 *      Eclipse RS422 receive message. If a matching header is found (0xEA),
 *      search each message in the receive message array for a matching message
 *      configuration (source, destination, cmd, length). 
 * 
 *      If a message header is found, determine if enough bytes occupy the circ 
 *      buffer to compose a valid message. 
 * 
 *      If a valid message length is found, calculate the CRC of the message. 
 *      The function accounts for head-tail wrap around, and can calculate the 
 *      CRC for a message that wraps around. If the CRC is valid, flush out 
 *      the data to the rxMsg's data array and advance the tail past the valid 
 *      message. 
 * 
 *      If a valid message is found, return true and set the input pointer value 
 *      to the EclipseRS422msg array's valid message index. 
 * 
 *      This function is also used to search for the software version reply
 *      for Eclipse's systems. In this implementation, the input parameter 
 *      returnMsgIndex is not required, and can be a dummy variable. 
 * 
 * Return: True if a message was successfully processed, false if invalid message. 
 *
 * Requirement Implemented : INT1.0102.S.IOP.1.001
 */

bool EclipseRS422_ProcessNewMessage( circBuffer_t * const rxCircBuffer, // circular buffer object
                                     const uint8_t rxMsgsSize, // Number of received messages in array
                                     EclipseRS422msg * const rxMsgs, // received messages array
                                     size_t * const returnMsgIndex ) // return parameter for a message index if a valid msg was found. 
{
    if ((NULL == rxCircBuffer) ||
            (NULL == rxMsgs))
    {
        return false;
    }

    while (true)
    {
        size_t incomingSize = cb_bytesUsed( rxCircBuffer );
        bool wasMsgStartFound = false; // Indicates whether the matching start sequence of as message has been found
        size_t msgIndex = 0; // Index into the received messages array of the message currently being processed

        /* Scan for a start condition for every byte in the msg. The start of a packet is indicated by the message preamble character */
        size_t dataByte_index;
        for (dataByte_index = 0; dataByte_index < incomingSize; dataByte_index++)
        {
            if (ECLIPSE_RS422_MESSAGE_PREAMBLE == cb_peek( rxCircBuffer, dataByte_index ))
            {
                if ((dataByte_index + ECLIPSE_RS422_MESSAGE_MIN_TOTAL_LENGTH) > incomingSize)
                {
                    break; // Preamble was located but not enough data has been received for a complete message
                }

                // Search for a matching message inside the circular buffer, for the entire length of an expected message. 
                for (msgIndex = 0; msgIndex < rxMsgsSize; msgIndex++)
                {
                    /* Look for match for command, destination, source and length */
                    if ((cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_CMD_INDEX ) == rxMsgs[msgIndex].msgConfig->cmd) &&
                            (cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_LENGTH_INDEX ) == rxMsgs[msgIndex].msgConfig->length) &&
                            ((cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX ) == rxMsgs[msgIndex].msgConfig->leftDestination) ||
                            (cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX ) == rxMsgs[msgIndex].msgConfig->rightDestination)) &&
                            ((cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_SOURCE_INDEX ) == rxMsgs[msgIndex].msgConfig->leftSource) ||
                            (cb_peek( rxCircBuffer, dataByte_index + ECLIPSE_RS422_MESSAGE_SOURCE_INDEX ) == rxMsgs[msgIndex].msgConfig->rightSource)))
                    {
                        wasMsgStartFound = true; // Indicate that a prospective message has been found
                        break; // Breaks for loop 
                    }
                }

                if (true == wasMsgStartFound)
                {
                    break;
                }
            }
        }

        /* Advance the tail to the first ECLIPSE_RS422_MESSAGE_PREAMBLE character (or all the way to head if none were found) */
        cb_advanceTail( rxCircBuffer, dataByte_index );

        if (false == wasMsgStartFound)
        {
            break; // All available data was processed and no matching message header sequence was found
        }

        /* Determine if sufficient data has been received for the message */
        incomingSize = cb_bytesUsed( rxCircBuffer );
        if (incomingSize < (rxMsgs[msgIndex].msgConfig->length + ECLIPSE_RS422_MESSAGE_LENGTH_HEADER_AND_CRC))
        {
            break;
        }

        /* Verify CRC */
        uint16_t calculatedCRC;
        size_t totalMsgLength = rxMsgs[msgIndex].msgConfig->length + ECLIPSE_RS422_MESSAGE_LENGTH_HEADER_AND_CRC;

        /* If "tail" < "head" then the CRC can be calculated all in one go. */
        if (rxCircBuffer->tail < rxCircBuffer->head)
        {
            calculatedCRC = CRC16_Calculate16bitCRC( rxCircBuffer->data + rxCircBuffer->tail,
                                                     totalMsgLength, // change this to -2 to calc valid crc 
                                                     ECLIPSE_RS422_CRC_SEED_VALUE );
        }
        else /* Head loops around end of buffer so CRC may need to be calculated in two steps */
        {
            size_t bytesToVerify = min( totalMsgLength, rxCircBuffer->capacity - rxCircBuffer->tail );

            calculatedCRC = CRC16_Calculate16bitCRC( rxCircBuffer->data + rxCircBuffer->tail,
                                                     bytesToVerify,
                                                     ECLIPSE_RS422_CRC_SEED_VALUE );

            size_t bytesRemaining = totalMsgLength - bytesToVerify;

            if (bytesRemaining > 0)
            {
                calculatedCRC = CRC16_Calculate16bitCRC( rxCircBuffer->data,
                                                         totalMsgLength - bytesToVerify,
                                                         calculatedCRC );
            }
        }

        /* If the CRC of the received message was invalid, advance the tail and return false. */
        if (0x0 != calculatedCRC)
        {
            cb_advanceTail( rxCircBuffer, 1 ); /* Message is invalid, discard */
            return false;
        }
        else
        {
            /* CRC is good. Copy message data. */
            cb_advanceTail( rxCircBuffer,
                            ECLIPSE_RS422_MESSAGE_DATA_START_OFFSET );

            if (NULL != rxMsgs[msgIndex].data)
            {
                cb_flushOut( rxCircBuffer,
                             rxMsgs[msgIndex].data, // linear buffer where data from circular buffer is loaded to
                             rxMsgs[msgIndex].msgConfig->length - 1 ); // number of bytes to be loaded from circular buffer into destination buffer (limited to data available in circular buffer)
            }
            rxMsgs[msgIndex].timeStamp_counts = 0;
            cb_advanceTail( rxCircBuffer, 2 );
            *returnMsgIndex = msgIndex;
            return true;
        }
    }
    return false; // Generic end condition for all above breaks in while true loop
}

/*
 * Function: EclipseRS422messages_ConstructTxMsg 
 * 
 * Description: Constructs an RS422 transmit message and flushes to the 
 *          transmit circular buffer. Inputs an array of ARINC429 words,
 *          a pointer to an EclipseRS422 message array, a pointer to the 
 *          desired transmit circular buffer, the number of ARINC429 words
 *          in the input array, the SDI of magnetic heading (this is an arbitrary 
 *          choice of word, could be anything), and the number of bytes to 
 *          flush to the transmit circular buffer. The number of bytes to flush
 *          equals the message length of the desired transmit message. 
 * 
 *          Message construction adds Eclipse's header, source, destination, msg 
 *          length, command, data, and appends the 16 bit crc to the end of the 
 *          message before flushing into the transmit circular buffer. 
 * 
 *          Guards against constructing a tx array larger than a circular buffer
 *          can handle. This must be maintained based on the circular buffer size. 
 * 
 * Return : None 
 *
 * Requirement Implemented: INT1.0102.S.IOP.1.003
 */
void EclipseRS422_ConstructTxMsg( EclipseRS422msg * const rs422TxMsg, /* Pointer to RS422 Eclipse message */
                                  circBuffer_t * const txBuff, /* Circular buffer destination to flush resultant array */
                                  uint32_t * const arincArray, /* Array of ARINC words to send. This param can be null */
                                  const size_t numArincWords, /* Number of ARINC words to send in the message */
                                  const uint8_t magHeadingSDI, /* SDI of magnetic heading to set L/R. Mag heading is arbitrary */
                                  const size_t numBytesToFlush ) /* Number of bytes to flush is the size of the desired tx message in bytes */
{
    if ((NULL == rs422TxMsg) ||
            (NULL == txBuff) ||
            (magHeadingSDI > 0x03) ||
            (numBytesToFlush > SIZE_OF_TX_CIRCBUFF_BYTES) ||
            (numArincWords > MAX_NUM_ARINC_WORDS_CONSTRUCT_MSG))
    {
        return;
    }

    /* The input arincArray CAN be null, but only if the numArincWords input is zero. */
    if ((NULL == arincArray) &&
            (0 != numArincWords))
    {
        return;
    }

    /* Modify the arinc array to calculate odd parity for each respective ARINC word */
    size_t counter;
    uint32_t * thisARINCWord = arincArray;
    uint32_t tempARINCWord = *thisARINCWord; // Create a copy of, but not a reference to, the input ARINC array. 

    /* Calculate and append (if needed) the odd parity of each ARINC Word */
    for (counter = 0; counter < numArincWords; counter++)
    {
        tempARINCWord &= 0x7FFFFFFF; // This should be unnecessary. 
        tempARINCWord ^= tempARINCWord >> 1;
        tempARINCWord ^= tempARINCWord >> 2;
        tempARINCWord = (tempARINCWord & 0x11111111U) * 0x11111111U;

        /* If the ARINC word has an even number of bits, toggle the 32nd bit. 
         * The 32nd bit of the input ARINC word should ALWAYS be zero.
         */
        if (0 == ((tempARINCWord >> 28) &1))
        {
            *thisARINCWord |= ARINC_PARITY_SET;
        }

        thisARINCWord++;
        tempARINCWord = *thisARINCWord;
    }

    /* Assemble header of messages */
    rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_PREAMBLE_INDEX] = ECLIPSE_RS422_MESSAGE_PREAMBLE;
    switch (magHeadingSDI)
    {
        case (0x01): // left case
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX] = rs422TxMsg->msgConfig->leftDestination;
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_SOURCE_INDEX] = rs422TxMsg->msgConfig->leftSource;
            break;
        case (0x03): // right case
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX] = rs422TxMsg->msgConfig->rightDestination;
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_SOURCE_INDEX] = rs422TxMsg->msgConfig->rightSource;
            break;
        default:
            // look back at this. SDI is an optional field, and lack of SDI shouldn't invalidate a tx msg 
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_DESTINATION_INDEX] = rs422TxMsg->msgConfig->leftDestination;
            rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_SOURCE_INDEX] = rs422TxMsg->msgConfig->leftSource;
            break;
    }
    rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_LENGTH_INDEX] = rs422TxMsg->msgConfig->length;
    rs422TxMsg->data[ECLIPSE_RS422_MESSAGE_CMD_INDEX] = rs422TxMsg->msgConfig->cmd;

    /* Create a pointer to the data portion of the eclipse txMsg */
    uint8_t* txMsgBuff = rs422TxMsg->data + ECLIPSE_RS422_MESSAGE_DATA_START_OFFSET;

    /* Iterate through ARINC raw word struct and store values, byte by byte, into rs422 output stream. */
    uint8_t arincWordCounter;

    for (arincWordCounter = 0; arincWordCounter < numArincWords; arincWordCounter++)
    {
        txMsgBuff[3] = (uint8_t) ((arincArray[arincWordCounter] >> ARINC_BYTE_THREE_OFFSET) & LS_BYTE_BITMASK);
        txMsgBuff[2] = (uint8_t) ((arincArray[arincWordCounter] >> ARINC_BYTE_TWO_OFFSET) & LS_BYTE_BITMASK);
        txMsgBuff[1] = (uint8_t) ((arincArray[arincWordCounter] >> ARINC_BYTE_ONE_OFFSET) & LS_BYTE_BITMASK);
        txMsgBuff[0] = (uint8_t) (arincArray[arincWordCounter] & LS_BYTE_BITMASK);
        txMsgBuff += NUM_BYTES_ARINC_MSG;
    }

    /* Calculate and append the CRC of the message */
    uint16_t crc = CRC16_Calculate16bitCRC( rs422TxMsg->data,
                                            txMsgBuff - rs422TxMsg->data,
                                            ECLIPSE_RS422_CRC_SEED_VALUE );
    txMsgBuff[0] = (uint8_t) ((crc >> NUM_BITS_IN_BYTE) & LS_BYTE_BITMASK);
    txMsgBuff[1] = crc & LS_BYTE_BITMASK;

    /* Flush the assembled RS422 tx message to the input tx message's data */
    cb_flushIn( txBuff,
                rs422TxMsg->data, /* Note: This is the FULL msg, not just the data portion */
                numBytesToFlush );
    return;
}

/*
 * Function: EclipseRS422messages_CreateARINCWords
 * 
 * Description: Creates ARINC429 words from received RS422 data. Received RS422
 *      data is in serial format and must compose a 32bit ARINC429 message from
 *      four received and verified bytes. The input param msgIdx is calculated 
 *      from the function EclipseRS422_ProcessNewMessage and tells which index
 *      of the input EclipseRS422msg array that a verified serial packet was 
 *      found. This ensures that only one verified packet can be used to compose
 *      ARINC message at a time. Each composed 32bit ARINC word will be input to
 *      the ProcessReceivedMessage function and processed into the input 
 *      ARINC429_RxMsgArray. 
 *
 * Return : None 
 *
 * Requirement Implemented : INT1.0102.S.IOP.1.002
 */
void EclipseRS422_CreateARINCWords( const EclipseRS422msg * const RS422Msg, /* Pointer to Eclipse rx msg array */
                                    ARINC429_RxMsgArray * const ArincMsgArray, /* Pointer to ARINC msg array */
                                    const size_t msgIdx, /* message index */
                                    const size_t numMsgsInRS422Array ) /* Total number of members in input EclipseRS422msg array */
{
    if ((NULL == RS422Msg) ||
            (NULL == ArincMsgArray) ||
            (msgIdx > numMsgsInRS422Array))
    {
        return;
    }

    const uint8_t numARINCMessages = (RS422Msg[msgIdx].msgConfig->length - 1) / NUM_BYTES_ARINC_MSG;

    if (numARINCMessages > MAX_NUM_ARINC_MESSAGES)
    {
        return; // Error, shouldn't happen. 
    }
    
    uint8_t counter;
    uint32_t arincWord;
    uint8_t * data = RS422Msg[msgIdx].data;
    for (counter = 0; counter < numARINCMessages; counter++)
    {
        // Note: Received label is in flipped format 
        arincWord = ((uint32_t) (data[0]) |
                ((uint32_t) (data[1]) << ARINC_BYTE_ONE_OFFSET) |
                ((uint32_t) (data[2]) << ARINC_BYTE_TWO_OFFSET) |
                ((uint32_t) (data[3]) << ARINC_BYTE_THREE_OFFSET));
        data += NUM_BYTES_ARINC_MSG;
        ARINC429_ProcessReceivedMessage( ArincMsgArray, arincWord );
    }
    return;
}

/*
 * Function: EclipseRS422message_processTimeout
 * 
 * Description: Processes a bus failure calculation if all messages in an 
 *      EclipseRS422msg array haven't received a valid message in the 
 *      configured amount of time. 
 * 
 * Return: True if invalid params or bus failure. False if valid bus 
 * 
 * Requirement Implemented: INT1.0102.S.IOP.1.004
 */
bool EclipseRS422_processBusFailure( EclipseRS422msg * const RS422Msg,
                                     const size_t numMsgs )
{
    if (NULL == RS422Msg)
    {
        return true; // Invalid msg. Return as if msg failure
    }
    size_t msgIdx;
    size_t numInvalidMsgs = 0;
    for (msgIdx = 0; msgIdx < numMsgs; msgIdx++)
    {
        RS422Msg[msgIdx].timeStamp_counts++;
        if (RS422Msg[msgIdx].timeStamp_counts >= RS422Msg[msgIdx].timeStamp_max_counts)
        {
            numInvalidMsgs++;
        }
    }
    return (numInvalidMsgs == numMsgs) ? true : false;
}

/* End EclipseRS422message.c source file */
