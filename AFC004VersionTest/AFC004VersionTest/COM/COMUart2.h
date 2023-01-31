/*************************************************************
 * Filename: COMUart2.h
 *  
 * Author Henry Gilbert
 * 
 * Date Created: 14 March 2022
 * 
 * Description: Contains all necessary function declarations and links the 
 *              interrupt service routines to the relevant interrupt vector. 
 * 
  All rights reserved. Copyright 2022. Archangel Systems Inc
 ************************************************************/

#ifndef COMUART2_H
#define COMUART2_H

/**************  Include Files  ************************/
//#include "COMtypedefs.h"
//#include "../AFC004.X/IOPConfig.h"
#include "CircularBuffer.h"
#include <stdint.h>
#include "../COM/pic_h/p30F6014A.h"

/* Interrupt Service routine linking to interrupt vector */
#define UART2_RxInterrupt __attribute__ ((interrupt,no_auto_psv)) _U2RXInterrupt
#define UART2_TxInterrupt __attribute__ ((interrupt,no_auto_psv)) _U2TXInterrupt

/* UART2 Transmit Interrupt Routine */
void UART2_TxInterrupt(void);

/* UART2 Receive Interrupt Routine */
void UART2_RxInterrupt(void);

/* UART2 Initialize Routine  */
void UART2_Initialize(uint16_t interruptConfig, /* Interrupt Configuration */
        uint16_t baudRate, /* Baud Rate Configuration */
        uint16_t modeConfig, /* UART Mode Configuration */
        uint16_t statusConfig, /* UART Status Configuration */
        circBuffer_t * uart2RxCircBuff, /* Pointer to the receive circular buffer */
        circBuffer_t * uart2TxCircBuff); /* Pointer to the transmit circular buffer */

/* Reads UART2 data to receive circular buffer */
void UART2_ReadToRxCircBuff(void);

/* UART2 Start Transmission  */
void UART2_TxStart(void);

#endif